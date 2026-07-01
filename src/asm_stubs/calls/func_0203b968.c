/* Destructor: tears down node->p_88 (sound-channel pool) and node->list_90 (double-list),
 * then dispatches to base destructor func_0203c900(node).
 *   func_0202a7dc(node->p_88); func_0203d194(node->p_88); node->p_88 = NULL;
 *   if (node->list_90) { NNSi_FndDestroyDoubleList(node->list_90); func_0203d194(node->list_90); }
 *   func_0203c900(node);
 */
extern void func_0202a7dc(void *p);
extern void func_0203d194(void *p);
extern void NNSi_FndDestroyDoubleList(void *list);
extern void func_0203c900(void *node);

asm void func_0203b968(void *node)
{
    stmdb sp!, {r4, lr}
    mov   r4, r0
    ldr   r0, [r4, #0x88]
    bl    func_0202a7dc
    ldr   r0, [r4, #0x88]
    bl    func_0203d194
    mov   r0, #0
    str   r0, [r4, #0x88]
    ldr   r0, [r4, #0x90]
    cmp   r0, #0
    beq   tail
    bl    NNSi_FndDestroyDoubleList
    ldr   r0, [r4, #0x90]
    bl    func_0203d194
tail:
    mov   r0, r4
    bl    func_0203c900
    ldmia sp!, {r4, pc}
}
