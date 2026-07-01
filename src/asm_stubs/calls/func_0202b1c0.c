/* Sound channel: if (!(state->flags & 0x20)) func_0202a7dc(&state->ch); state->flags |= 0x20;
 * Sets the "channel running/started" flag atomically with a one-shot start callback.
 */
extern void func_0202a7dc(void *ch);

asm void func_0202b1c0(int *state)
{
    stmdb sp!, {r4, lr}
    mov   r4, r0
    ldr   r0, [r4]
    tst   r0, #0x20
    bne   skip
    add   r0, r4, #4
    bl    func_0202a7dc
skip:
    ldr   r0, [r4]
    orr   r0, r0, #0x20
    str   r0, [r4]
    ldmia sp!, {r4, pc}
}
