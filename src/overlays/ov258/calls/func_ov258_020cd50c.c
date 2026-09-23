/* Brain start of the ov258 actor: move 1 with no next move, the +0x38 timer rolls between the +0x224
 * and +0x228 bounds, the +0xc point is the actor's +0xb0 pose, the +0x58 sound bank is 0x180 with a
 * +0x460 partner (else 0x17b), +0x56 is cleared to -1 and the three brain slots get 020cd748 (0),
 * 020cdbb8 (1) and 020cd9b0 (2). */
extern int func_02023eb4(int bound);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov258_020cd748(void);
extern void func_ov258_020cdbb8(void);
extern void func_ov258_020cd9b0(void);

void func_ov258_020cd50c(int *node)
{
    int *state = (int *)node[1];

    *(signed char *)(*state + 0x1c6) = 1;
    *(signed char *)(*state + 0x1c7) = -1;
    {
        int lo = *(int *)(*state + 0x224);
        int span = *(int *)(*state + 0x228) - lo;

        if (span < 0) {
            span = -span;
        }
        state[0xe] = lo + func_02023eb4(span + 1);
    }
    state[3] = *state + 0xb0;
    *(short *)(state + 0x16) = *(int *)(*state + 0x460) != 0 ? 0x180 : 0x17b;
    *((signed char *)state + 0x56) = -1;
    func_0203c634(node, 0, func_ov258_020cd748);
    func_0203c634(node, 1, func_ov258_020cdbb8);
    func_0203c634(node, 2, func_ov258_020cd9b0);
}
