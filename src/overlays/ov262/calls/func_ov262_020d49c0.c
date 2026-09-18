/* Approach decision of the ov261 enemy (and its byte-identical twin). Picks the +0x70 target
 * from the +0x3ac slot byte: none ends the state with sub-state 2; a target sharing the +0x3a8
 * part's +4 owner plays animation 0 (looped), resets the +0x6c clock and hands off to d0f90;
 * otherwise bits 1 and 7 of the +0x60 flag high byte are set, animation 2 (looped) plays and the
 * tick hands off to d0e4c. */
typedef unsigned char u8;

extern int func_ov262_020d402c(int *state, int slot);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov107_020c9264(int actor, int anim, int flag);
extern void func_ov262_020d4bd0(int *node);
extern void func_ov262_020d4a8c(int *node);

void func_ov262_020d49c0(int *node)
{
    int *state = (int *)node[1];
    int actor;
    unsigned short *hw;
    unsigned int h;

    state[0x1c] = func_ov262_020d402c(state, *(u8 *)(*state + 0x3ac));
    if (state[0x1c] == 0) {
        *(u8 *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    actor = *state;
    if (*(int *)(*(int *)(actor + 0x3a8) + 4) == *(int *)(actor + 4)) {
        func_ov107_020c9264(actor, 0, 1);
        state[0x1b] = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov262_020d4bd0);
        return;
    }
    hw = (unsigned short *)(actor + 0x60);
    h = *hw;
    /* hw60.hi |= 0x82 -- explicit-shift form (bitfield |= adds a redundant mask) */
    *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 0x82) << 0x18) >> 0x10);
    func_ov107_020c9264(*state, 2, 1);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov262_020d4a8c);
}
