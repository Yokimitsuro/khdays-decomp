extern void func_0202aa9c(void *arg);

asm void func_ov064_020b6c50(void *arg0, char *arg1)
{
    stmdb   sp!, {r3, lr}
    ldrsb   r2, [r1]
    cmp     r2, #2
    cmpne   r2, #3
    cmpne   r2, #4
    ldmneia sp!, {r3, pc}
    ldrb    r0, [r0, #0x694]
    mov     r0, r0, lsl #0x1f
    movs    r0, r0, lsr #0x1f
    ldmeqia sp!, {r3, pc}
    add     r0, r1, #4
    bl      func_0202aa9c
    ldmia   sp!, {r3, pc}
}
