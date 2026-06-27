extern void func_ov107_020c9264(void *r0, int r1, int r2);
extern void func_ov107_020c9ee8(void *r0, int r1, int r2);
extern int func_0203c634(void *r0, int r1, void *r2);
extern void func_ov242_020d46c0(void *p);

asm void func_ov242_020d4670(void *r0)
{
    stmfd   sp!, {r3, r4, r5, lr}
    mov     r5, r0
    ldr     r4, [r5, #4]
    mov     r1, #1
    ldr     r0, [r4]
    mov     r2, r1
    bl      func_ov107_020c9264
    ldr     r0, [r4]
    mov     r1, #0
    ldr     r0, [r0, #0x39c]
    mov     r2, #1
    bl      func_ov107_020c9ee8
    mov     r0, #0
    strb    r0, [r4, #0x40]
    ldrsb   r1, [r5, #0x20]
    ldr     r2, =func_ov242_020d46c0
    mov     r0, r5
    bl      func_0203c634
    ldmfd   sp!, {r3, r4, r5, pc}
}
