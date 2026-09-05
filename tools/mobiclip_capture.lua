-- One-shot DeSmuME capture for the ov024 MobiClip decoder.
--
-- Load this script while the EU game is running, then start a cutscene. It
-- hooks the stable ARM call site around the copied payload, captures the exact
-- 0x454-byte state and referenced frame planes before/after one decoded frame,
-- and writes a JSON manifest plus raw files under scratch/mobiclip/captures.

local ROOT = "E:/KH 3582/decomp/scratch/mobiclip/captures"
local MAX_CAPTURES = 1
local SKIP_DECODES = 30
local BITSTREAM_BYTES = 0x10000

local BEFORE_CALL = 0x02085a20
local AFTER_CALL = 0x02085a24
local ITCM_PAYLOAD = 0x01ff9a64
local OVERLAY_PAYLOAD = 0x0208c8c4
local STATE_SIZE = 0x454
local TRANSFORM4_ITCM = 0x01ffba48
local TRANSFORM4_OVERLAY = 0x0208e8a8
local TRANSFORM8_ITCM = 0x01ffb890
local TRANSFORM8_OVERLAY = 0x0208e6f0
local VLC_ITCM = 0x01ffda00
local VLC_OVERLAY = 0x02090860
local COLOR_CONVERTER = 0x02086004

local capture_count = 0
local decode_count = 0
local active = nil
local transform4 = nil
local transform8 = nil
local vlc = nil
local color = nil
local transform4_count = 0
local transform8_count = 0
local vlc_count = 0
local color_count = 0

local function hex(value)
    return string.format("0x%08x", value)
end

local function read_u32(address)
    return memory.readdword(address)
end

local function unsigned(value)
    if value < 0 then
        return value + 4294967296
    end
    return value
end

local function write_range(path, address, length)
    local file = io.open(path, "wb")
    if not file then
        error("cannot write " .. path .. " (create the captures directory first)")
    end
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

local function read_block(address, size)
    local values = {}
    for y = 0, size - 1 do
        for x = 0, size - 1 do
            values[#values + 1] = memory.readbyte(address + y * 0x100 + x)
        end
    end
    return values
end

local function read_coefficients(state, size)
    local values = {}
    for i = 0, size * size - 1 do
        values[#values + 1] = memory.readdwordsigned(state + 0x1b4 + i * 4)
    end
    return values
end

local function read_words(address, count)
    local values = {}
    for i = 0, count - 1 do
        values[#values + 1] = memory.readword(address + i * 2)
    end
    return values
end

local function read_dwords(address, count)
    local values = {}
    for i = 0, count - 1 do
        values[#values + 1] = unsigned(memory.readdword(address + i * 4))
    end
    return values
end

local function write_array(file, name, values, comma)
    file:write("  \"" .. name .. "\": [")
    for i, value in ipairs(values) do
        if i > 1 then file:write(", ") end
        file:write(tostring(value))
    end
    file:write("]" .. (comma and "," or "") .. "\n")
end

local function write_transform(info, coefficients, observed)
    local file = assert(io.open(info.path, "w"))
    file:write("{\n")
    file:write(string.format("  \"size\": %d,\n", info.size))
    file:write(string.format("  \"sourceEntry\": \"%s\",\n", hex(info.source_entry)))
    file:write(string.format("  \"runtimeEntry\": \"%s\",\n", hex(info.runtime_entry)))
    file:write(string.format("  \"stateAddress\": \"%s\",\n", hex(info.state)))
    file:write(string.format("  \"destinationAddress\": \"%s\",\n", hex(info.destination)))
    write_array(file, "coefficients", coefficients, true)
    write_array(file, "prediction", info.prediction, true)
    write_array(file, "observed", observed, false)
    file:write("}\n")
    file:close()
end

local function write_vlc(info)
    local file = assert(io.open(info.path, "w"))
    file:write("{\n")
    file:write(string.format("  \"sourceEntry\": \"%s\",\n", hex(info.source_entry)))
    file:write(string.format("  \"runtimeEntry\": \"%s\",\n", hex(info.runtime_entry)))
    file:write(string.format("  \"stateAddress\": \"%s\",\n", hex(info.state)))
    file:write(string.format("  \"tableAddress\": \"%s\",\n", hex(info.table_address)))
    file:write(string.format("  \"quantScanAddress\": \"%s\",\n", hex(info.quant_scan)))
    file:write(string.format("  \"coefficientCount\": %d,\n", info.coefficient_count))
    file:write(string.format("  \"cursorBefore\": \"%s\",\n", hex(info.cursor_before)))
    file:write(string.format("  \"bitsRemainingBefore\": %d,\n", info.bits_before))
    file:write(string.format("  \"reservoirBefore\": \"%s\",\n", hex(info.reservoir_before)))
    file:write(string.format("  \"cursorAfter\": \"%s\",\n",
        hex(unsigned(memory.getregister("arm9.r1")))))
    file:write(string.format("  \"bitsRemainingAfter\": %d,\n",
        memory.getregister("arm9.r2")))
    file:write(string.format("  \"reservoirAfter\": \"%s\",\n",
        hex(unsigned(memory.getregister("arm9.r3")))))
    write_array(file, "nextInputWords", info.next_words, true)
    write_array(file, "quantScan", info.quant_scan_entries, true)
    write_array(file, "coefficients", read_coefficients(
        info.state, info.coefficient_count == 16 and 4 or 8), false)
    file:write("}\n")
    file:close()
end

local function prefix(index)
    return ROOT .. "/frame_" .. string.format("%04d", index)
end

local function capture_planes(stem, phase, state, width, height)
    local records = {}
    local groups = {
        { name = "luma", offset = 0x0c, bytes = width * height },
        { name = "chroma", offset = 0x24, bytes = math.floor(width * height / 2) },
    }
    for _, group in ipairs(groups) do
        for i = 0, 5 do
            local address = read_u32(state + group.offset + i * 4)
            if address ~= 0 then
                local name = stem .. "_" .. phase .. "_" .. group.name .. i .. ".bin"
                write_range(ROOT .. "/" .. name, address, group.bytes)
                records[#records + 1] = {
                    name = name,
                    address = address,
                    bytes = group.bytes,
                }
            end
        end
    end
    return records
end

local function write_manifest(info)
    local file = assert(io.open(info.base .. "_manifest.json", "w"))
    file:write("{\n")
    file:write(string.format("  \"capture\": %d,\n", info.index))
    file:write(string.format("  \"stateAddress\": \"%s\",\n", hex(info.state)))
    file:write(string.format("  \"payloadAddress\": \"%s\",\n", hex(info.payload)))
    file:write(string.format("  \"bitstreamAddress\": \"%s\",\n", hex(info.bitstream)))
    file:write(string.format("  \"bitstreamBytesCaptured\": %d,\n", BITSTREAM_BYTES))
    file:write(string.format("  \"decoderReturnBytes\": %d,\n", info.return_bytes))
    file:write(string.format("  \"width\": %d,\n", info.width))
    file:write(string.format("  \"height\": %d,\n", info.height))
    file:write("  \"stateSize\": 1108,\n")
    file:write("  \"files\": {\n")
    file:write(string.format("    \"beforeState\": \"%s_before_state.bin\",\n", info.stem))
    file:write(string.format("    \"afterState\": \"%s_after_state.bin\",\n", info.stem))
    file:write(string.format("    \"bitstream\": \"%s_bitstream.bin\"\n", info.stem))
    file:write("  },\n")
    file:write("  \"planes\": [\n")
    for i, record in ipairs(info.planes) do
        local comma = i < #info.planes and "," or ""
        file:write(string.format(
            "    {\"file\": \"%s\", \"address\": \"%s\", \"bytes\": %d}%s\n",
            record.name, hex(record.address), record.bytes, comma))
    end
    file:write("  ]\n}\n")
    file:close()
end

local function before_decode()
    if capture_count >= MAX_CAPTURES or active then
        return
    end

    local state = memory.getregister("arm9.r0")
    local payload = memory.getregister("arm9.r1")
    if payload ~= ITCM_PAYLOAD and payload ~= OVERLAY_PAYLOAD then
        return
    end

    local width = read_u32(state + 0x04)
    local height = read_u32(state + 0x08)
    if width == 0 or height == 0 or width > 1024 or height > 1024 then
        print("mobiclip_capture: rejected implausible state " .. hex(state))
        return
    end

    decode_count = decode_count + 1
    if decode_count <= SKIP_DECODES then
        return
    end

    capture_count = capture_count + 1
    local stem = "frame_" .. string.format("%04d", capture_count)
    local base = prefix(capture_count)
    local bitstream = read_u32(state + 0x00)
    write_range(base .. "_before_state.bin", state, STATE_SIZE)
    write_range(base .. "_bitstream.bin", bitstream, BITSTREAM_BYTES)
    local planes = capture_planes(stem, "before", state, width, height)

    active = {
        index = capture_count,
        stem = stem,
        base = base,
        state = state,
        payload = payload,
        bitstream = bitstream,
        width = width,
        height = height,
        planes = planes,
    }
    print(string.format(
        "mobiclip_capture: before frame %d state=%s payload=%s %dx%d",
        capture_count, hex(state), hex(payload), width, height))
end

local function after_decode()
    if not active then
        return
    end

    write_range(active.base .. "_after_state.bin", active.state, STATE_SIZE)
    local after_planes = capture_planes(
        active.stem, "after", active.state, active.width, active.height)
    for _, record in ipairs(after_planes) do
        active.planes[#active.planes + 1] = record
    end
    active.return_bytes = memory.getregister("arm9.r0")
    write_manifest(active)
    print(string.format(
        "mobiclip_capture: saved frame %d (%d decoder bytes consumed)",
        active.index, active.return_bytes))
    active = nil
end

local function finish_transform(size)
    local info = size == 4 and transform4 or transform8
    if not info then
        return
    end
    local coefficients = read_coefficients(info.state, size)
    local observed = read_block(info.destination, size)
    write_transform(info, coefficients, observed)
    print(string.format(
        "mobiclip_capture: saved %dx%d transform -> %s",
        size, size, info.path))
    if size == 4 then
        transform4 = nil
    else
        transform8 = nil
    end
end

local function begin_transform(size, source_entry, runtime_entry)
    if capture_count == 0 then
        return
    end
    if size == 4 and (transform4_count >= 1 or transform4) then
        return
    end
    if size == 8 and (transform8_count >= 1 or transform8) then
        return
    end

    -- The 8x8 routine also dispatches the four-4x4 path. Its incoming
    -- reservoir MSB selects the actual 8x8 transform.
    if size == 8 and unsigned(memory.getregister("arm9.r3")) < 0x80000000 then
        return
    end

    local count
    if size == 4 then
        transform4_count = transform4_count + 1
        count = transform4_count
    else
        transform8_count = transform8_count + 1
        count = transform8_count
    end

    local state = unsigned(memory.getregister("arm9.r0"))
    local destination = unsigned(memory.getregister("arm9.r11"))
    local return_address = unsigned(memory.getregister("arm9.r14"))
    return_address = return_address - (return_address % 2)
    local stem = "frame_" .. string.format("%04d", capture_count)
    local info = {
        size = size,
        state = state,
        destination = destination,
        prediction = read_block(destination, size),
        source_entry = source_entry,
        runtime_entry = runtime_entry,
        path = ROOT .. "/" .. stem .. "_transform" .. size .. "x" .. size ..
               "_" .. string.format("%04d", count) .. ".json",
    }
    if size == 4 then
        transform4 = info
        memory.registerexec(return_address, 2, function() finish_transform(4) end)
    else
        transform8 = info
        memory.registerexec(return_address, 2, function() finish_transform(8) end)
    end
end

local function register_transform(source_entry, itcm_entry, size)
    memory.registerexec(itcm_entry, 2, function()
        begin_transform(size, source_entry, itcm_entry)
    end)
    memory.registerexec(source_entry, 2, function()
        begin_transform(size, source_entry, source_entry)
    end)
end

local function finish_vlc()
    if not vlc then
        return
    end
    write_vlc(vlc)
    print("mobiclip_capture: saved VLC block -> " .. vlc.path)
    vlc = nil
end

local function begin_vlc(source_entry, runtime_entry)
    if capture_count == 0 or vlc_count >= 1 or vlc then
        return
    end

    local state = unsigned(memory.getregister("arm9.r0"))
    local quant_scan = unsigned(memory.getregister("arm9.r12"))
    local coefficient_count
    if quant_scan == state + 0x174 then
        coefficient_count = 16
    elseif quant_scan == state + 0x74 then
        coefficient_count = 64
    else
        return
    end

    vlc_count = vlc_count + 1
    local cursor = unsigned(memory.getregister("arm9.r1"))
    local return_address = unsigned(memory.getregister("arm9.r14"))
    return_address = return_address - (return_address % 2)
    local stem = "frame_" .. string.format("%04d", capture_count)
    vlc = {
        source_entry = source_entry,
        runtime_entry = runtime_entry,
        state = state,
        table_address = unsigned(read_u32(state + 0x3b8)),
        quant_scan = quant_scan,
        coefficient_count = coefficient_count,
        cursor_before = cursor,
        bits_before = memory.getregister("arm9.r2"),
        reservoir_before = unsigned(memory.getregister("arm9.r3")),
        next_words = read_words(cursor, 32),
        quant_scan_entries = read_dwords(quant_scan, coefficient_count),
        path = ROOT .. "/" .. stem .. "_vlc_" ..
               string.format("%04d", vlc_count) .. ".json",
    }
    memory.registerexec(return_address, 2, finish_vlc)
end

local function register_vlc(source_entry, itcm_entry)
    memory.registerexec(itcm_entry, 2, function()
        begin_vlc(source_entry, itcm_entry)
    end)
    memory.registerexec(source_entry, 2, function()
        begin_vlc(source_entry, source_entry)
    end)
end

local function write_color_manifest(info)
    local file = assert(io.open(info.path, "w"))
    file:write("{\n")
    file:write("  \"kind\": \"ycocg_to_rgb555\",\n")
    file:write(string.format("  \"entry\": \"%s\",\n", hex(COLOR_CONVERTER)))
    file:write(string.format("  \"lumaAddress\": \"%s\",\n", hex(info.luma)))
    file:write(string.format("  \"chromaAddress\": \"%s\",\n", hex(info.chroma)))
    file:write(string.format("  \"destinationAddress\": \"%s\",\n", hex(info.destination)))
    file:write(string.format("  \"width\": %d,\n", info.width))
    file:write(string.format("  \"height\": %d,\n", info.height))
    file:write("  \"lumaStride\": 256,\n")
    file:write("  \"chromaStride\": 256,\n")
    file:write(string.format(
        "  \"destinationStrideBytes\": %d,\n", info.destination_stride))
    file:write("  \"files\": {\n")
    file:write(string.format("    \"luma\": \"%s\",\n", info.luma_file))
    file:write(string.format("    \"chroma\": \"%s\",\n", info.chroma_file))
    file:write(string.format("    \"rgb555\": \"%s\"\n", info.output_file))
    file:write("  }\n}\n")
    file:close()
end

local function finish_color()
    if not color then
        return
    end
    write_range(
        ROOT .. "/" .. color.output_file,
        color.destination,
        color.destination_stride * color.height)
    write_color_manifest(color)
    print("mobiclip_capture: saved YCoCg/RGB555 frame -> " .. color.path)
    color = nil
end

local function begin_color()
    if capture_count == 0 or color_count >= 1 or color then
        return
    end

    local args = unsigned(memory.getregister("arm9.r0"))
    local width = unsigned(read_u32(args + 0x10))
    local height = unsigned(read_u32(args + 0x14))
    local destination_stride = unsigned(read_u32(args + 0x0c))
    if width == 0 or width > 0x100 or width % 16 ~= 0 or
       height == 0 or height > 0x400 or height % 2 ~= 0 or
       destination_stride < width * 2 then
        return
    end

    color_count = color_count + 1
    local stem = "frame_" .. string.format("%04d", capture_count) .. "_color_" ..
                 string.format("%04d", color_count)
    local return_address = unsigned(memory.getregister("arm9.r14"))
    return_address = return_address - (return_address % 2)
    color = {
        luma = unsigned(read_u32(args + 0x00)),
        chroma = unsigned(read_u32(args + 0x04)),
        destination = unsigned(read_u32(args + 0x08)),
        destination_stride = destination_stride,
        width = width,
        height = height,
        luma_file = stem .. "_luma.bin",
        chroma_file = stem .. "_chroma.bin",
        output_file = stem .. "_rgb555.bin",
        path = ROOT .. "/" .. stem .. ".json",
    }
    write_range(ROOT .. "/" .. color.luma_file, color.luma, 0x100 * height)
    write_range(
        ROOT .. "/" .. color.chroma_file,
        color.chroma,
        0x100 * math.floor(height / 2))
    memory.registerexec(return_address, 2, finish_color)
end

memory.registerexec(BEFORE_CALL, 2, before_decode)
memory.registerexec(AFTER_CALL, 2, after_decode)
register_transform(TRANSFORM4_OVERLAY, TRANSFORM4_ITCM, 4)
register_transform(TRANSFORM8_OVERLAY, TRANSFORM8_ITCM, 8)
register_vlc(VLC_OVERLAY, VLC_ITCM)
memory.registerexec(COLOR_CONVERTER, 2, begin_color)

print("mobiclip_capture: armed for one frame")
print("  output: " .. ROOT)
print("  skipping the first " .. SKIP_DECODES .. " decoder calls")
print("  start a cutscene; stop the script after the manifest is written")

while true do
    emu.frameadvance()
end
