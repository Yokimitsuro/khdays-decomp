asm void *func_02010128(void *base, void *table)
{
    cmp r1, #0
    ldreq r0, [r0]
    ldrneh r0, [r0, #0xa]
    addne r0, r1, r0
    ldrne r0, [r0, #4]
    bx lr
}
