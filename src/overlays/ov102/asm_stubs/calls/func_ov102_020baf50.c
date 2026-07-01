extern void func_0202aa9c(void);

asm void func_ov102_020baf50(void *arg0, void *arg1, void *arg2, void *arg3)
{
    stmfd   sp!, {lr}
    sub     sp, sp, #0xc
    mov     lr, r0
    ldrb    r0, [lr, #0x694]
    mov     ip, r1
    mov     r0, r0, lsl #0x1f
    movs    r0, r0, lsr #0x1f
    addeq   sp, sp, #0xc
    ldmeqfd sp!, {pc}
    ldr     r0, [ip, #0x10]
    cmp     r0, #2
    addne   sp, sp, #0xc
    ldmnefd sp!, {pc}
    add     r0, lr, #0x8c
    add     r0, r0, #0x400
    add     r3, sp, #0
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    ldr     r0, [lr, #0x20]
    add     lr, ip, #0xb8
    ldrh    r0, [r0, #0x80]
    sub     r0, r0, #0x8000
    mov     r0, r0, lsl #0x10
    mov     r0, r0, lsr #0x10
    add     r0, r0, #0x8000
    strh    r0, [ip, #0x90]
    ldrh    r0, [ip, #0x14]
    orr     r0, r0, #0x20
    strh    r0, [ip, #0x14]
    ldmia   r3, {r0, r1, r2}
    stmia   lr, {r0, r1, r2}
    add     r0, ip, #0x14
    bl      func_0202aa9c
    add     sp, sp, #0xc
    ldmfd   sp!, {pc}
}
