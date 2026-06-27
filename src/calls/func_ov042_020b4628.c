extern void func_0202a818(void);

asm void func_ov042_020b4628(void)
{
    stmdb   sp!, {r4, lr}
    mov     r4, r0
    ldr     r0, [r4, #0]
    cmp     r0, #0
    ldmeqia sp!, {r4, pc}
    cmp     r0, #1
    ldmneia sp!, {r4, pc}
    add     r0, r4, #4
    bl      func_0202a818
    cmp     r0, #0
    movne   r0, #0
    strne   r0, [r4, #0]
    ldmia   sp!, {r4, pc}
}
