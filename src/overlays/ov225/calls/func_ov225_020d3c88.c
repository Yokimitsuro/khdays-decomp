/* Slam tick of the ov225 enemy. The +0x5c timer accumulates the owner's rate; once it passes
 * 0x770 with a +0x78 target or 0x1a90 without, reaction 0x14b mode 0x14 fires at the +8 point
 * (the +0x75 byte marks it). Between 0x1540 and 0x2178 with a target, or 0x2200 and 0x2ec0
 * without, the strike sweep (ov225 0a08) runs with mode 7. Once the +4 owner's +0xad byte
 * clears, sub-state 2 is requested and the action ends. */
typedef unsigned char u8;

extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_ov225_020d0a08(int *state, int mode, void *params);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov225_020d3c88(int *node)
{
    int *state = (int *)node[1];

    state[0x17] += *(int *)(*node + 0x2c);
    if (*(u8 *)((char *)state + 0x75) == 0) {
        if ((state[0x1e] != 0 && state[0x17] >= 0x770) || (state[0x1e] == 0 && state[0x17] >= 0x1a90)) {
            *(u8 *)((char *)state + 0x75) = 1;
            func_ov107_020c5af8(*state, 0x14b, 0x14, (void *)state[2]);
        }
    }
    if ((state[0x1e] != 0 && state[0x17] >= 0x1540 && state[0x17] <= 0x2178)
        || (state[0x1e] == 0 && state[0x17] >= 0x2200 && state[0x17] <= 0x2ec0)) {
        func_ov225_020d0a08(state, 7, 0);
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    *(u8 *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
