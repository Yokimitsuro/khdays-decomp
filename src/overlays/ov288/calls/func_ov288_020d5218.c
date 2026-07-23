/* Charge up until the timer saturates, then pick a random victim from the list at +0x398 and
 * commit to the attack. The timer at state[0xd] accumulates the owner's per-frame delta and is
 * clamped at 1.0; once there, the default target (+0x190) is armed, and if the count at +0x3b8
 * is positive a uniformly-random index into the list replaces it. The attack only starts when
 * either the range query fails or the distance it reports is over 0x800: bit 0 of the hw60 high
 * byte goes up and the action byte becomes 1.
 *
 * Matched byte-exact 2026-07-23, first compile. One of three byte-identical siblings. */
extern void func_ov107_020c5c54(int obj, void *p);
extern int func_02023eb4(int n);
extern void *func_01fffd70(void *list);
extern void *func_01fffd8c(void *list, void *node);
extern int func_ov107_020cab14(int obj, void *out);
extern int FX_Sqrt(int x);
extern void func_0203c634(void *node, int idx, void *cb);

void func_ov288_020d5218(int *node) {
    int *owner = (int *)node[0];
    int *state = (int *)node[1];
    int d;

    state[0xd] = state[0xd] + *(int *)((int)owner + 0x2c);
    if (state[0xd] < 0x1000) {
        return;
    }
    state[0xd] = 0x1000;
    func_ov107_020c5c54(state[0], (void *)(state[0] + 0x190));
    if (*(int *)(state[0] + 0x3b8) > 0) {
        int n = func_02023eb4(*(int *)(state[0] + 0x3b8));
        void *p = func_01fffd70((void *)(state[0] + 0x398));
        int i = 0;
        while (p != 0) {
            if (i >= n) {
                func_ov107_020c5c54(state[0], p);
                break;
            }
            p = func_01fffd8c((void *)(state[0] + 0x398), p);
            i++;
        }
    }
    if (func_ov107_020cab14(state[0], &d) != 0) {
        if (FX_Sqrt(d) <= 0x800) {
            return;
        }
    }
    {
        unsigned short hw60 = *(unsigned short *)(state[0] + 0x60);
        *(unsigned short *)(state[0] + 0x60) =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 1) << 0x18) >> 0x10);
    }
    *(char *)(state[0] + 0x1c7) = 1;
    func_0203c634(node, *(signed char *)((int)node + 0x20), 0);
}
