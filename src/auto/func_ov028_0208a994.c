asm void func_ov028_0208a994(void *ctx, unsigned char *key, int keylen)
{
    stmdb sp!, {r4, r5, r6, r7, r8, lr}
    mov   r6, #0
    str   r6, [r0]
    mov   r7, r6
    mov   r4, r6
    str   r6, [r0, #4]
_l1:
    add   r3, r0, r4
    strb  r4, [r3, #8]
    add   r4, r4, #1
    cmp   r4, #0x100
    blt   _l1
    mov   r8, #0xff
    mov   r3, #0
_l2:
    ldrb  ip, [r1, r6]
    add   r5, r0, r8
    ldrb  r4, [r5, #8]
    add   ip, r7, ip
    add   r6, r6, #1
    add   ip, r4, ip
    and   r7, ip, #0xff
    add   lr, r0, r7
    ldrb  ip, [lr, #8]
    cmp   r6, r2
    movhs r6, r3
    strb  r4, [lr, #8]
    strb  ip, [r5, #8]
    subs  r8, r8, #1
    bpl   _l2
    ldmia sp!, {r4, r5, r6, r7, r8, pc}
}
