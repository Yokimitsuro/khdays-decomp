extern void func_ov107_020c5c54(void *r0, int r1, int r2, int r3);
extern int func_0203c634(void *r0, int r1, int r2);

asm void func_ov294_020d1f94(void *r0)
{
    stmfd   sp!, {r3, r4, lr}
    sub     sp, sp, #0xc
    mov     r4, r0
    ldr     r0, [r4, #4]
    ldr     r3, [r0]
    ldrh    r1, [r3, #0x60]
    mov     r1, r1, lsl #0x18
    mov     r1, r1, lsr #0x18
    tst     r1, #1
    addeq   sp, sp, #0xc
    ldmeqfd sp!, {r3, r4, pc}
    add     r1, r3, #0x100
    ldrsb   r2, [r1, #0xc9]
    add     r1, sp, #0
    strb    r2, [r3, #0x1c7]
    ldr     r2, [r0, #4]
    ldmia   r2, {r2, r3, ip}
    add     r3, r3, #0x900
    str     r2, [sp]
    str     r3, [sp, #4]
    str     ip, [sp, #8]
    ldr     r0, [r0]
    bl      func_ov107_020c5c54
    ldrsb   r1, [r4, #0x20]
    mov     r0, r4
    mov     r2, #0
    bl      func_0203c634
    add     sp, sp, #0xc
    ldmfd   sp!, {r3, r4, pc}
}
