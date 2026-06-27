/* List ForEach callback (caller func_0203c10c): if (node->flags_5c & 2) return;
 * else invoke node->cb_6c (if non-null), then invoke node->cb_74(node, node->arg_84) if non-null.
 * Two-stage dispatch on a node holding two function pointers.
 */
asm void func_0203c86c(void *node)
{
    stmdb sp!, {r4, lr}
    mov   r4, r0
    ldr   r2, [r4, #0x5c]
    mov   r2, r2, lsl #0x1e
    movs  r2, r2, asr #0x1f
    ldmneia sp!, {r4, pc}
    ldr   r2, [r4, #0x6c]
    cmp   r2, #0
    beq   skip1
    blx   r2
skip1:
    ldr   r2, [r4, #0x74]
    cmp   r2, #0
    ldmeqia sp!, {r4, pc}
    ldr   r1, [r4, #0x84]
    mov   r0, r4
    blx   r2
    ldmia sp!, {r4, pc}
}
