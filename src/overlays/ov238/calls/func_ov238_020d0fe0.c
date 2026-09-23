/* Recover tick of the ov238 actor: once its guard flag (+0x60 bit 0) is up, the +0x28 rest is rolled
 * between +0x224 and +0x228, pose 0x16 loops and the queued +0x1c9 move becomes next. */
typedef unsigned short u16;
typedef struct { u16 lo : 8; u16 hi : 8; } flags16;

extern int func_02023eb4(int bound);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov238_020d0fe0(int *node)
{
    int *state = (int *)node[1];
    int lo;
    int span;

    if ((((flags16 *)(*state + 0x60))->lo & 1) == 0) {
        return;
    }
    lo = *(int *)(*state + 0x224);
    span = *(int *)(*state + 0x228) - lo;
    if (span < 0) {
        span = -span;
    }
    state[0xa] = lo + func_02023eb4(span + 1);
    func_ov107_020c9264(*state, 0x16, 1);
    *(signed char *)(*state + 0x1c7) = *(signed char *)(*state + 0x1c9);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
