extern void func_ov030_020b4048(void *r0, int r1);

asm void func_ov030_020b4000(void *r0)
{
    stmdb   sp!, {r4, lr}
    mov     r1, #0x2
    mov     r4, r0
    bl      func_ov030_020b4048
    mov     r0, #0x5
    strb    r0, [r4, #0x12c]
    mov     r0, #0
    str     r0, [r4, #0x130]
    ldmia   sp!, {r4, pc}
}
