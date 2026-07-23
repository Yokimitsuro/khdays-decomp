/* Ease the pursuit speed towards its cap and, once the target byte at state[3] clears,
 * lock it at 1.0 and roll the next hold time.
 *
 * The travelled distance at state[0x11] accumulates the owner's per-frame delta, is turned
 * into a fraction of 0x2aa by FX_Inv, and biased by 0xcc into the speed field at +0x390,
 * clamped to 0x1000. When the gate byte is clear the speed is pinned to 0x1000, a hold time
 * is rolled uniformly between the bounds at +0x224/+0x228, and the action byte at +0x1c7 is
 * set to 2 before re-registering the think callback. */
extern int FX_Inv(int a, int b);
extern int func_02023eb4(int scale);
extern void func_0203c634(void *node, int idx, void *cb);

void func_ov277_020d2e0c(int *node) {
    int *owner = (int *)node[0];
    int *state = (int *)node[1];
    int v;
    int lo;

    state[0x11] = state[0x11] + *(int *)((int)owner + 0x2c);
    v = FX_Inv(state[0x11], 0x2aa);
    *(int *)(state[0] + 0x390) = v + 0xcc;
    if (*(int *)(state[0] + 0x390) > 0x1000) {
        *(int *)(state[0] + 0x390) = 0x1000;
    }
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    *(int *)(state[0] + 0x390) = 0x1000;
    lo = *(int *)(state[0] + 0x224);
    v = *(int *)(state[0] + 0x228) - lo;
    if (v < 0) {
        v = -v;
    }
    state[0x13] = lo + func_02023eb4(v + 1);
    *(char *)(state[0] + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((int)node + 0x20), 0);
}
