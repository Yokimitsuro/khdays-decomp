/* Wake check of an ov255 state: once bit 0 of the owner's +0x60 low byte is set, +0x70 clears,
 * +0x74 is raised, the +0x54 cooldown is rolled in [+0x224, +0x228] and the owner's +0x1c9 default
 * sub-state is requested (+0x1c7). */
typedef unsigned short u16;
struct Flags60 { u16 lo : 8; u16 hi : 8; };

extern int func_02023eb4(int n);
extern void func_0203c634(int *node, int slot, void *cb);

static inline int RandRange(int lo, int hi)
{
    int d = hi - lo;

    if (d < 0) {
        d = -d;
    }
    return lo + func_02023eb4(d + 1);
}

void func_ov255_020cd420(int *node)
{
    int *state = (int *)node[1];

    if ((((struct Flags60 *)(*state + 0x60))->lo & 1) == 0) {
        return;
    }
    state[0x1c] = 0;
    state[0x1d] = 1;
    state[0x15] = RandRange(*(int *)(*state + 0x224), *(int *)(*state + 0x228));
    *(signed char *)(*state + 0x1c7) = *(signed char *)(*state + 0x1c9);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
