extern void func_0202accc(void);
extern void func_01fff774(void);

asm void func_ov070_020b8918(void)
{
    stmfd   sp!, {r4, r5, r6, lr}
    mov     r5, r1
    mov     r6, r0
    mov     r1, r5, lsl #0x10
    mov     r4, r2
    add     r0, r6, #8
    add     r2, r6, #0xe8
    mov     r3, r1, asr #0x10
    mov     r1, #0
    bl      func_0202accc
    mov     r1, r5, lsl #0x10
    add     r0, r6, #8
    add     r2, r6, #0xe8
    mov     r3, r1, asr #0x10
    mov     r1, #2
    bl      func_0202accc
    mov     r2, r4
    add     r0, r6, #8
    mov     r1, #0
    bl      func_01fff774
    add     r0, r6, #8
    mov     r2, r4
    mov     r1, #2
    bl      func_01fff774
    ldmfd   sp!, {r4, r5, r6, pc}
}
