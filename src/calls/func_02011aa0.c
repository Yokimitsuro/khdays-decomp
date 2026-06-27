/* FindNitroChunk(NitroFile *file, u32 fourcc) - scans subchunk table at file+header_off */
asm void *func_02011aa0(void *file, unsigned int fourcc)
{
    ldrh   r2, [r0, #0xc]
    ldrh   r12, [r0, #0xe]
    mov    r3, #0
    add    r0, r0, r2
    cmp    r12, #0
    bls    end
loop:
    ldr    r2, [r0]
    cmp    r2, r1
    bxeq   lr
    add    r2, r3, #1
    mov    r2, r2, lsl #0x10
    ldr    r3, [r0, #4]
    cmp    r12, r2, lsr #16
    add    r0, r0, r3
    mov    r3, r2, lsr #0x10
    bhi    loop
end:
    mov    r0, #0
    bx     lr
}
