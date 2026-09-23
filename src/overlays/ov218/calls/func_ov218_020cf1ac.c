/* Start of an ov218 flash helper: it takes its owner's +0x3a4 model (+4), gives it the shadow draw
 * hook (020cf144) with itself as owner and hides bit 1 of its +0x5c flags; layers 0 and 2 start
 * (mode 0, 1) and layer 4 on step 5, the owner's +0x394 flag is set, +8 clears and the node moves on
 * to 020cf28c. */
extern void func_0203b9fc(int rig, int channel, int a, int b);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov218_020cf144(void);
extern void func_ov218_020cf28c(void);

void func_ov218_020cf1ac(int *node)
{
    int *state = (int *)node[1];

    state[1] = *(int *)(*state + 0x3a4);
    *(void **)(state[1] + 0x6c) = func_ov218_020cf144;
    *(int **)(state[1] + 0x84) = state;
    *(int *)(state[1] + 0x5c) &= ~2;
    state[3] = 5;
    func_0203b9fc(state[1], 0, 0, 1);
    func_0203b9fc(state[1], 2, 0, 1);
    func_0203b9fc(state[1], 4, (short)state[3], 1);
    *(int *)(*state + 0x394) = 1;
    state[2] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov218_020cf28c);
}
