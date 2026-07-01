extern void func_ov042_020b403c(void);

asm void func_ov042_020b4358(void)
{
    stmdb   sp!, {r4, lr}
    mov     r4, r1
    ldr     r1, [r4, #0]
    cmp     r1, #0
    cmpne   r1, #2
    ldmneia sp!, {r4, pc}
    cmp     r1, #0
    bne     _020b4358_store
    bl      func_ov042_020b403c
_020b4358_store:
    mov     r0, #1
    str     r0, [r4, #0]
    ldmia   sp!, {r4, pc}
}
