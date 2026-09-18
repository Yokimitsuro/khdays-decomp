/* Wander entry of the ov220 enemy. Looks for a target into the
 * actor's +0x390 slot: without one the state ends with sub-state 2. Otherwise the +0x48 side is
 * rolled (0/1) after the +0x44 slot is cleared to -1 and the +0x5c clock zeroed, the +0x18 timer
 * is set to +0x224 + rand(|+0x228 - +0x224| + 1) and the tick hands off to the wander state. */
typedef unsigned char u8;

extern int func_ov107_020cab14(int actor, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern int func_02023eb4(int bound);
extern void func_ov220_020d2b08(int *node);

void func_ov220_020d2a64(int *node)
{
    int *state = (int *)node[1];
    int lo;
    int d;

    *(int *)(*state + 0x390) = func_ov107_020cab14(*state, 0);
    if (*(int *)(*state + 0x390) == 0) {
        *(u8 *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    state[0x11] = -1;
    state[0x17] = 0;
    *(u8 *)(state + 0x16) = func_02023eb4(2);
    lo = *(int *)(*state + 0x224);
    d = *(int *)(*state + 0x228) - lo;
    state[6] = lo + func_02023eb4((d < 0 ? -d : d) + 1);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov220_020d2b08);
}
