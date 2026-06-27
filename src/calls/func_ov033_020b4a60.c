extern void func_02016b60(void);
extern void func_0202aa9c(void);

asm void func_ov033_020b4a60(void)
{
    stmfd   sp!, {r4, lr}
    mov     r4, r0
    ldr     r0, [r4]
    cmp     r0, #1
    ldmnefd sp!, {r4, pc}
    ldr     r0, [r4, #0x80]
    ldr     r2, [r4, #4]
    mov     r1, #2
    bl      func_02016b60
    add     r0, r4, #8
    bl      func_0202aa9c
    ldmfd   sp!, {r4, pc}
}
