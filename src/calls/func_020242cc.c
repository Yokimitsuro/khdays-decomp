extern unsigned short data_02041dd4[];

asm int func_020242cc(int idx)
{
    ldr  r1, =data_02041dd4
    mov  r2, r0, lsl #1
    ldrh r1, [r1, r2]
    cmp  r1, #0
    bxeq lr
    add  r1, r1, #0x4000000
    ldrh r1, [r1]
    tst  r1, #0x2000
    addne r0, r0, #2
    bx   lr
}
