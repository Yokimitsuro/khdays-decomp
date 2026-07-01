extern void *func_0203c5c0(void *r0, int r1, int r2, int r3);
extern void func_ov294_020d1da4(void *p);

asm void func_ov294_020d1c00(void *arg)
{
    stmfd   sp!, {r3, r4, lr}
    sub     sp, sp, #0xc
    mov     r2, #0
    str     r2, [sp]
    add     r1, sp, #8
    str     r1, [sp, #4]
    mov     r4, r0
    ldr     r0, [r4, #0x3c]
    ldr     r3, =func_ov294_020d1da4
    mov     r1, #0x64
    mov     r2, #0x10
    bl      func_0203c5c0
    ldr     r0, [sp, #8]
    str     r4, [r0]
    ldr     r0, [sp, #8]
    str     r0, [r4, #0x214]
    add     sp, sp, #0xc
    ldmfd   sp!, {r3, r4, pc}
}
