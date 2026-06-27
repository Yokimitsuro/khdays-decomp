extern int func_0203c634(void *r0, int r1, int r2);
extern void func_ov301_020cc63c(void *p);
extern void func_ov301_020cc338(void *p);
extern void func_ov301_020cc458(void *p);

asm void func_ov301_020cc2a4(void *r0)
{
    stmfd   sp!, {r3, r4, r5, lr}
    mov     r4, r0
    ldr     r3, [r4, #4]
    mov     r2, #0
    ldr     r1, [r3]
    sub     r5, r2, #1
    strb    r2, [r1, #0x1c6]
    ldr     r1, [r3]
    ldr     r2, =func_ov301_020cc63c
    strb    r5, [r1, #0x1c7]
    ldr     r5, [r3]
    mov     r1, #1
    ldr     r5, [r5, #0x388]
    ldr     lr, [r5, #8]
    mov     ip, lr, lsl #0x18
    mov     ip, ip, lsr #0x18
    bic     ip, ip, #1
    bic     lr, lr, #0xff
    and     ip, ip, #0xff
    orr     ip, lr, ip
    str     ip, [r5, #8]
    ldr     ip, [r3]
    add     ip, ip, #0xb0
    str     ip, [r3, #4]
    bl      func_0203c634
    ldr     r2, =func_ov301_020cc338
    mov     r0, r4
    mov     r1, #0
    bl      func_0203c634
    ldr     r2, =func_ov301_020cc458
    mov     r0, r4
    mov     r1, #2
    bl      func_0203c634
    ldmfd   sp!, {r3, r4, r5, pc}
}
