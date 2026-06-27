asm char *func_0201f9ec(char *dst, const char *src, int n)
{
    stmdb sp!, {r3, lr}
    mov lr, r0
    cmp r2, #0
    ldmeqia sp!, {r3, pc}
copy_loop:
    ldrsb r3, [r1], #1
    mov ip, lr
    strb r3, [lr], #1
    ldrsb r3, [ip]
    cmp r3, #0
    bne dec
    subs r2, r2, #1
    ldmeqia sp!, {r3, pc}
    mov r1, #0
pad_loop:
    strb r1, [lr], #1
    subs r2, r2, #1
    bne pad_loop
    ldmia sp!, {r3, pc}
dec:
    subs r2, r2, #1
    bne copy_loop
    ldmia sp!, {r3, pc}
}
