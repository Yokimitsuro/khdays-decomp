asm void *func_020170c8(void *p, int idx)
{
    cmp  r0, #0
    beq  _ret0
    ldrh r2, [r0, #0xc]
    ldr  r2, [r0, r2]
    add  ip, r0, r2
    adds r3, ip, #8
    beq  _zero
    ldrb r0, [ip, #9]
    cmp  r1, r0
    bhs  _zero
    ldrh r2, [ip, #0xe]
    ldrh r0, [r3, r2]
    add  r2, r3, r2
    add  r2, r2, #4
    mla  r1, r0, r1, r2
    b    _chk
_zero:
    mov  r1, #0
_chk:
    cmp  r1, #0
    ldrne r0, [r1]
    addne r0, ip, r0
    bxne lr
_ret0:
    mov  r0, #0
    bx   lr
}
