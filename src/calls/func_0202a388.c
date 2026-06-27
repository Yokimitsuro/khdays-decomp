/* Sound: register a sequence and initialize its player slot.
 *   slot->seq = SND_RegisterSeq(seq_id, arg3);
 *   tick = func_0201f634(1);
 *   func_0202a208(slot, arg1, tick, arg3);
 *   return 1;
 */
extern void *SND_RegisterSeq(int seq_id, int arg);
extern int   func_0201f634(int on);
extern void  func_0202a208(void *slot, int arg1, int tick, int arg3);

asm int func_0202a388(void *slot, int arg1, int seq_id, int arg3)
{
    stmdb sp!, {r4, r5, r6, lr}
    mov   r4, r3
    mov   r6, r0
    mov   r5, r1
    mov   r0, r2
    mov   r1, r4
    bl    SND_RegisterSeq
    mov   r1, #1
    str   r0, [r6, #0xc]
    bl    func_0201f634
    mov   r2, r0
    mov   r1, r5
    mov   r3, r4
    mov   r0, r6
    bl    func_0202a208
    mov   r0, #1
    ldmia sp!, {r4, r5, r6, pc}
}
