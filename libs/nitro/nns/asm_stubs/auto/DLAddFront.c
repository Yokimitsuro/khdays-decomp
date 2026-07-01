asm void *DLAddFront(void *item, void *node)
{
    str r0, [r1, #4]
    mov r2, #0
    str r2, [r1]
    cmp r0, #0
    strne r1, [r0]
    mov r0, r1
    bx lr
}
