extern void func_ov292_020d3e58(void *r0);
extern int func_0203c634(void *r0, int r1, int r2);

asm void func_ov292_020d4654(void *r0)
{
    stmfd   sp!, {r3, r4, r5, lr}
    mov     r5, r0
    ldr     r4, [r5, #4]
    mov     r0, r4
    bl      func_ov292_020d3e58
    ldr     r0, [r4, #4]
    ldrb    r0, [r0, #0xad]
    cmp     r0, #0
    ldmnefd sp!, {r3, r4, r5, pc}
    ldr     r0, [r4]
    mov     r1, #4
    strb    r1, [r0, #0x1c7]
    ldrsb   r1, [r5, #0x20]
    mov     r0, r5
    mov     r2, #0
    bl      func_0203c634
    ldmfd   sp!, {r3, r4, r5, pc}
}
