asm void func_ov007_0204ce94(void *p)
{
    ldr     ip, [r0, #0x78]
    ldr     r3, [r0, #0x74]
    mov     r1, ip, lsl #1
    ldrh    r2, [r3, r1]
    mov     r1, #0
    cmp     r2, #0
    beq     _exit
_loop:
    mov     ip, ip, lsl #1
    ldrh    r2, [r3, ip]
    cmp     r2, #0xa
    bne     _copy
    ldr     r2, [r0, #0x78]
    add     r2, r2, #1
    str     r2, [r0, #0x78]
    b       _exit
_copy:
    ldr     r3, [r0, #0x78]
    add     r2, r0, r1, lsl #1
    add     r3, r3, #1
    str     r3, [r0, #0x78]
    ldr     r3, [r0, #0x74]
    add     r1, r1, #1
    ldrh    r3, [r3, ip]
    strh    r3, [r2, #0x7c]
    ldr     ip, [r0, #0x78]
    ldr     r3, [r0, #0x74]
    mov     r2, ip, lsl #1
    ldrh    r2, [r3, r2]
    cmp     r2, #0
    bne     _loop
_exit:
    add     r0, r0, r1, lsl #1
    mov     r1, #0
    strh    r1, [r0, #0x7c]
    bx      lr
}
