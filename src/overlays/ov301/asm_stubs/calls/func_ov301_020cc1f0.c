extern void func_0203b9fc(void *r0, int r1, int r2, int r3);
extern void func_0203c7ac(void *r0, int r1);

asm void func_ov301_020cc1f0(void *r0, int r1, int r2)
{
    stmfd   sp!, {r4, r5, r6, lr}
    mov     r5, r1
    mov     r6, r0
    mov     r4, r2
    mov     r1, r5, lsl #0x10
    ldr     r0, [r6, #0x384]
    mov     r3, r4
    mov     r2, r1, asr #0x10
    mov     r1, #2
    bl      func_0203b9fc
    mov     r1, r5, lsl #0x10
    ldr     r0, [r6, #0x384]
    mov     r3, r4
    mov     r2, r1, asr #0x10
    mov     r1, #0
    bl      func_0203b9fc
    ldr     r0, [r6, #0x384]
    mov     r1, #0
    bl      func_0203c7ac
    ldmfd   sp!, {r4, r5, r6, pc}
}
