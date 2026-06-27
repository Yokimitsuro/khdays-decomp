/* func_02010c2c (ARM): allocates a 16-byte node from heap at &ctx[+0x24]
 * via NNSi_AllocFromHeadOfExpHeap(.., 16, 4); on success stores
 *   node[0] = arg, node[4] = old_head, node[8] = ctx[+0x28], node[0xc] = ctx[+0x2c],
 *   ctx[+0x2c] = node;
 * returns 1; returns 0 on alloc failure.
 */
extern void *NNSi_AllocFromHeadOfExpHeap(void *h, int sz, int align);

asm int func_02010c2c(void *ctx, void *arg)
{
    stmdb sp!, {r4, r5, r6, lr}
    mov   r6, r0
    ldr   r4, [r6, #0x24]
    mov   r5, r1
    add   r0, r6, #0x24
    mov   r1, #0x10
    mov   r2, #4
    bl    NNSi_AllocFromHeadOfExpHeap
    cmp   r0, #0
    moveq r0, #0
    ldmeqia sp!, {r4, r5, r6, pc}
    str   r5, [r0]
    str   r4, [r0, #4]
    ldr   r1, [r6, #0x28]
    str   r1, [r0, #8]
    ldr   r1, [r6, #0x2c]
    str   r1, [r0, #0xc]
    str   r0, [r6, #0x2c]
    mov   r0, #1
    ldmia sp!, {r4, r5, r6, pc}
}
