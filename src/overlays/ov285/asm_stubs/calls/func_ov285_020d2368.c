extern void *func_ov107_020cab14(void *r0, int r1);
extern int func_0203c634(void *r0, int r1, void *r2);
extern void func_ov107_020c9264(void *r0, int r1, int r2);
extern void *func_02023eb4(int);
extern void func_ov285_020d23f0(void *p);

asm void func_ov285_020d2368(void *r0)
{
    stmfd   sp!, {r3, r4, r5, lr}
    mov     r5, r0
    ldr     r4, [r5, #4]
    mov     r1, #0
    ldr     r0, [r4]
    bl      func_ov107_020cab14
    str     r0, [r4, #0x18]
    cmp     r0, #0
    bne     _L_44
    ldr     r0, [r4]
    mov     r1, #2
    strb    r1, [r0, #0x1c7]
    ldrsb   r1, [r5, #0x20]
    mov     r0, r5
    mov     r2, #0
    bl      func_0203c634
    ldmfd   sp!, {r3, r4, r5, pc}
_L_44:
    mov     r0, #0
    str     r0, [r4, #0x28]
    mov     r1, #1
    ldr     r0, [r4]
    mov     r2, r1
    bl      func_ov107_020c9264
    ldr     r0, =0x00003001
    bl      func_02023eb4
    add     r0, r0, #0x1000
    str     r0, [r4, #0x2c]
    ldrsb   r1, [r5, #0x20]
    ldr     r2, =func_ov285_020d23f0
    mov     r0, r5
    bl      func_0203c634
    ldmfd   sp!, {r3, r4, r5, pc}
}
