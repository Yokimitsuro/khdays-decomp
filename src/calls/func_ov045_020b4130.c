extern void func_0202a634(void);
extern void func_ov045_020b476c(void);
extern void *data_ov045_020b4bf4;

asm void func_ov045_020b4130(void)
{
    stmfd   sp!, {r4, lr}
    mov     r4, r0
    add     r0, r4, #0xdf0
    add     r3, r0, #0x2000
    add     r0, r4, #0x2000
    mov     r1, #0
    strb    r1, [r0, #0xdf0]
    str     r1, [r3, #0x114]
    ldrb    r2, [r4, #9]
    ldr     r1, =data_ov045_020b4bf4
    add     r0, r3, #4
    add     r3, r2, #7
    mov     r2, #1
    bl      func_0202a634
    mov     r0, r4
    bl      func_ov045_020b476c
    ldmfd   sp!, {r4, pc}
}
