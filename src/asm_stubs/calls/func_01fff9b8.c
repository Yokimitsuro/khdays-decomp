/* Sound event/timer trigger (ITCM): early-out unless globals + node state are all valid:
 *   if (*data_0204c22c == 0)       return;          // subsystem off
 *   if (node->u16_2  != 0)         return;          // already active
 *   if (node->p_0c   == 0)         return;          // no handler installed
 *   func_01fffa60(node->u16_10, node->u16_12 + 1, 1 /-r3-/, node);
 */
extern char data_0204c22c[];
extern void func_01fffa60(int a, int b, int c, void *node);

asm void func_01fff9b8(void *node)
{
    stmdb sp!, {r3, lr}
    ldr   r1, =data_0204c22c
    mov   r3, r0
    ldr   r0, [r1]
    cmp   r0, #0
    ldmeqia sp!, {r3, pc}
    ldrh  r0, [r3, #2]
    cmp   r0, #0
    ldmneia sp!, {r3, pc}
    ldr   r0, [r3, #0xc]
    cmp   r0, #0
    ldmeqia sp!, {r3, pc}
    ldrh  r2, [r3, #0x12]
    ldrh  r1, [r3, #0x10]
    mov   r3, #1
    add   r2, r2, #1
    bl    func_01fffa60
    ldmia sp!, {r3, pc}
}
