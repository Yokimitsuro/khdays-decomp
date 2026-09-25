-- One-shot DeSmuME capture of the two MobiClip kernels that run in place from ov024 .rodata.
--
-- KH Days never reaches either kernel on its own: the player always blits in display mode 0
-- (no deblocking post-filter) and every cutscene stream carries IMA ADPCM audio (coding 3), not
-- FastAudio (coding 2). This script forces each path exactly once during a cutscene and records
-- the kernel's inputs and outputs, so tools/mobiclip_deblock.py and tools/mobiclip_fastaudio.py
-- can replay them against their semantic models:
--
--   * deblock: at the blit call (0x020842a4) the mode register r3 is set to 2 for one frame, so
--     func_ov024_02085ab8 allocates its planes and runs the filter at 0x02092e60 (both edge
--     directions). The picture of that one frame is the filtered copy; nothing else changes.
--   * FastAudio: on one ADPCM entry that does not start a frame, the dispatcher (0x02085c8c) is
--     made to take coding 2 for that call. The channel block (0x1d0 bytes) is saved first and put
--     back afterwards, and the stream cursor is advanced by the 0x80 bytes the ADPCM block would
--     have used, so the stream stays in sync. One 256-sample block of that channel is noise.
--
-- Load the script while the EU game is running (Tools > Lua Scripting > New Lua Script Window),
-- start any cutscene and wait for both "saved" lines; then stop the script.

local ROOT = "E:/KH 3582/decomp/scratch/mobiclip/kernel_captures"
local SKIP_BLITS = 30            -- frames shown before the deblock capture
local SKIP_AUDIO = 40            -- eligible audio entries before the FastAudio capture

local BLIT_CALL = 0x020842a4     -- bl func_ov024_0208505c; r3 = display mode
local DEBLOCK = 0x02092e60
local AUDIO_DISPATCH = 0x02085c8c
local FASTAUDIO = 0x02087318
local CHANNEL_STRIDE = 0x14f8
local CHANNEL_BYTES = 0x1d0

local blits = 0
local deblock_state = "waiting"  -- waiting -> forced -> done
local audio_entries = 0
local audio_state = "waiting"    -- waiting -> forced -> done
local audio = nil

local function unsigned(value)
    if value < 0 then
        return value + 4294967296
    end
    return value
end

local function reg(name)
    return unsigned(memory.getregister("arm9." .. name))
end

local function u32(address)
    return unsigned(memory.readdword(address))
end

local function write_range(path, address, length)
    local file = assert(io.open(path, "wb"), "cannot write " .. path .. " (create the directory)")
    local offset = 0
    while offset < length do
        local count = math.min(1024, length - offset)
        local bytes = memory.readbyterange(address + offset, count)
        local chars = {}
        for i = 1, count do
            chars[i] = string.char(bytes[i] or 0)
        end
        file:write(table.concat(chars))
        offset = offset + count
    end
    file:close()
end

local function read_bytes(address, length)
    local out = {}
    local bytes = memory.readbyterange(address, length)
    for i = 1, length do
        out[i] = bytes[i] or 0
    end
    return out
end

local function write_json(path, fields)
    local file = assert(io.open(path, "w"))
    local parts = {}
    for _, pair in ipairs(fields) do
        local value = pair[2]
        if type(value) == "string" then
            value = '"' .. value .. '"'
        end
        parts[#parts + 1] = string.format('  "%s": %s', pair[1], tostring(value))
    end
    file:write("{\n" .. table.concat(parts, ",\n") .. "\n}\n")
    file:close()
end

-- deblocking post-filter ----------------------------------------------------------------

local deblock = nil

local function finish_deblock()
    memory.registerexec(deblock.return_address, 2, nil)
    local rows = deblock.height
    write_range(ROOT .. "/deblock_after_luma.bin", deblock.dst_luma, 0x100 * rows)
    write_range(ROOT .. "/deblock_after_chroma.bin", deblock.dst_chroma, 0x100 * math.floor(rows / 2))
    write_json(ROOT .. "/deblock.json", {
        {"kernel", "deblock"},
        {"width", deblock.width},
        {"height", deblock.height},
        {"quantiser", deblock.qp},
        {"vertical_only", deblock.vertical_only},
        {"before_luma", "deblock_before_luma.bin"},
        {"before_chroma", "deblock_before_chroma.bin"},
        {"clip_table", "deblock_clip_table.bin"},
        {"after_luma", "deblock_after_luma.bin"},
        {"after_chroma", "deblock_after_chroma.bin"},
    })
    deblock_state = "done"
    print("mobiclip_kernel_capture: saved deblock -> " .. ROOT .. "/deblock.json")
end

local function begin_deblock()
    if deblock_state ~= "forced" or deblock then
        return
    end
    local req = reg("r0")
    deblock = {
        src_luma = u32(req + 0x00),
        src_chroma = u32(req + 0x04),
        dst_luma = u32(req + 0x08),
        dst_chroma = u32(req + 0x0c),
        width = u32(req + 0x10),
        height = u32(req + 0x14),
        qp = u32(req + 0x18),
        table = u32(req + 0x1c),
        vertical_only = u32(req + 0x20),
        return_address = reg("r14"),
    }
    local rows = deblock.height
    write_range(ROOT .. "/deblock_before_luma.bin", deblock.src_luma, 0x100 * rows)
    write_range(ROOT .. "/deblock_before_chroma.bin", deblock.src_chroma, 0x100 * math.floor(rows / 2))
    write_range(ROOT .. "/deblock_clip_table.bin", deblock.table, 0x180)
    memory.registerexec(deblock.return_address, 2, finish_deblock)
end

local function on_blit_call()
    blits = blits + 1
    if deblock_state == "waiting" and blits >= SKIP_BLITS then
        memory.setregister("arm9.r3", 2)
        deblock_state = "forced"
    end
end

-- FastAudio ------------------------------------------------------------------------------

local function finish_fastaudio()
    memory.registerexec(audio.fastaudio_return, 2, nil)
    write_range(ROOT .. "/fastaudio_after_channel.bin", audio.chan, CHANNEL_BYTES)
    write_range(ROOT .. "/fastaudio_output.bin", audio.output, 0x200)
    write_json(ROOT .. "/fastaudio.json", {
        {"kernel", "fastaudio"},
        {"stride", 2},
        {"block", "fastaudio_block.bin"},
        {"before_channel", "fastaudio_before_channel.bin"},
        {"after_channel", "fastaudio_after_channel.bin"},
        {"output", "fastaudio_output.bin"},
    })
    print("mobiclip_kernel_capture: saved FastAudio -> " .. ROOT .. "/fastaudio.json")
end

local function begin_fastaudio()
    if audio_state ~= "forced" or not audio or audio.fastaudio_return then
        return
    end
    if reg("r0") ~= audio.chan then
        return
    end
    audio.output = u32(audio.chan + 4)
    audio.fastaudio_return = reg("r14")
    write_range(ROOT .. "/fastaudio_before_channel.bin", audio.chan, CHANNEL_BYTES)
    write_range(ROOT .. "/fastaudio_block.bin", u32(audio.chan), 0x28)
    memory.registerexec(audio.fastaudio_return, 2, finish_fastaudio)
end

local function restore_audio()
    memory.registerexec(audio.dispatch_return, 2, nil)
    memory.writeword(audio.ctx + 0x1c, 3)
    for i = 1, CHANNEL_BYTES do
        memory.writebyte(audio.chan + i - 1, audio.saved[i])
    end
    memory.writedword(audio.cursor_ptr, audio.cursor + 0x80)
    audio_state = "done"
end

local function on_audio_dispatch()
    if audio_state ~= "waiting" then
        return
    end
    local ctx = reg("r0")
    if memory.readword(ctx + 0x1c) ~= 3 or u32(ctx + 0xcc) == u32(ctx + 0xc8) or u32(ctx + 0xa4) ~= 0 then
        return
    end
    audio_entries = audio_entries + 1
    if audio_entries < SKIP_AUDIO then
        return
    end
    local chan = u32(ctx + 0x58) + u32(ctx + 0xd0) * CHANNEL_STRIDE
    local cursor_ptr = u32(ctx + 0x34)
    audio = {
        ctx = ctx,
        chan = chan,
        saved = read_bytes(chan, CHANNEL_BYTES),
        cursor_ptr = cursor_ptr,
        cursor = u32(cursor_ptr),
        dispatch_return = reg("r14"),
    }
    memory.writeword(ctx + 0x1c, 2)
    memory.writedword(chan + 0x1cc, 2)
    audio_state = "forced"
    memory.registerexec(audio.dispatch_return, 2, restore_audio)
end

memory.registerexec(BLIT_CALL, 2, on_blit_call)
memory.registerexec(DEBLOCK, 2, begin_deblock)
memory.registerexec(AUDIO_DISPATCH, 2, on_audio_dispatch)
memory.registerexec(FASTAUDIO, 2, begin_fastaudio)

print("mobiclip_kernel_capture: armed (deblock after " .. SKIP_BLITS .. " frames, FastAudio after "
      .. SKIP_AUDIO .. " audio entries)")
print("  output: " .. ROOT)
print("  start a cutscene and wait for both 'saved' lines")

while true do
    emu.frameadvance()
end
