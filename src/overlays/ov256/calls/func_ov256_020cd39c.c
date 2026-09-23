/* Start of the ov256 actor's brain: move 1 is current and none pending (+0x1c6 = 1, +0x1c7 = -1), the
 * idle time +0x50 is rolled between the +0x224 / +0x228 bounds, +0xc points at the +0xb0 anchor and
 * the three slots take the think (020cd430), watch (020cd8f0) and facing (020cd740) handlers. */
extern int func_02023eb4(int n);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov256_020cd430(void);
extern void func_ov256_020cd8f0(void);
extern void func_ov256_020cd740(void);

void func_ov256_020cd39c(int *node)
{
    int *state = (int *)node[1];
    int v;
    int lo;

    *(signed char *)(*state + 0x1c6) = 1;
    *(signed char *)(*state + 0x1c7) = -1;
    lo = *(int *)(*state + 0x224);
    v = *(int *)(*state + 0x228) - lo;
    if (v < 0) {
        v = -v;
    }
    state[0x14] = lo + func_02023eb4(v + 1);
    state[3] = *state + 0xb0;
    func_0203c634(node, 0, func_ov256_020cd430);
    func_0203c634(node, 1, func_ov256_020cd8f0);
    func_0203c634(node, 2, func_ov256_020cd740);
}
