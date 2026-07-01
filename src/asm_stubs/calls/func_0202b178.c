/* Channel reset/restore: if (flag) { clear bit 0x20, call func_0202a634 on inner state,
 *   and if (state.flags & 8) copy 3 words from state[0x13c..] -> state[0xa8..]; } return 1.
 */
extern void func_0202a634(void *p);

asm int func_0202b178(unsigned *state, int flag)
{
    stmdb sp!, {r4, lr}
    mov   r4, r0
    cmp   r1, #0
    beq   end
    ldr   r12, [r4]
    add   r0, r4, #4
    bic   r12, r12, #0x20
    str   r12, [r4]
    bl    func_0202a634
    ldr   r0, [r4]
    tst   r0, #8
    beq   end
    add   r0, r4, #0x13c
    add   r3, r4, #0xa8
    ldmia r0, {r0, r1, r2}
    stmia r3, {r0, r1, r2}
end:
    mov   r0, #1
    ldmia sp!, {r4, pc}
}
