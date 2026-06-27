extern void *data_0204ad4c;

asm void *func_0201b578(int idx)
{
    ldr  r1, =data_0204ad4c
    ldr  r3, [r1]
    ldr  r2, [r3, #0x8c]
    ldr  r1, [r2, #0x24]
    cmp  r1, #0
    moveq r2, #0
    addne r2, r2, r1
    cmp  r2, #0
    moveq r0, #0
    bxeq lr
    cmp  r0, #0
    movlt r0, #0
    bxlt lr
    ldr  r1, [r2]
    cmp  r0, r1
    movhs r0, #0
    bxhs lr
    add  r0, r2, r0, lsl #2
    ldr  r1, [r0, #4]
    ldr  r0, [r3, #0x8c]
    cmp  r1, #0
    moveq r0, #0
    addne r0, r0, r1
    bx   lr
}
