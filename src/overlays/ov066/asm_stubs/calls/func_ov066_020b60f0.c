extern void func_01fff774(void);
extern void func_0202accc(void);

asm void func_ov066_020b60f0(void *arg0, void *arg1, void *arg2, void *arg3)
{
    stmfd   sp!, {r4, lr}
    mov     r4, r0
    mov     r0, #1
    mov     r1, #0
    str     r0, [r4, #0x10]
    mov     r3, r1
    add     r0, r4, #0x14
    add     r2, r4, #0xf4
    str     r1, [r4, #0x11c]
    bl      func_0202accc
    add     r0, r4, #0x14
    add     r2, r4, #0xf4
    mov     r1, #2
    mov     r3, #0
    bl      func_0202accc
    mov     r1, #0
    mov     r2, r1
    add     r0, r4, #0x14
    bl      func_01fff774
    add     r0, r4, #0x14
    mov     r1, #2
    mov     r2, #0
    bl      func_01fff774
    ldmfd   sp!, {r4, pc}
}
