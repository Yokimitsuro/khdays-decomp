/* Hover release decision of the ov261 enemy (and its byte-identical twin): when the +0x48 slot
 * of the +0x3a0 grab list has kind 1 the actor sets bit 7 and clears bit 0 of the +0x60 flag high
 * byte, releases the list's first entry (slot +0x3ad, carried), clears the +0x3a4 grab and the
 * +0x2c word and ends the state with sub-state 2. Otherwise the +0x34 lift eases by a fiftieth
 * towards 0x2000 above the +0x13c height, the +0xc quaternion is decomposed into the +0x74 axis
 * (and a discarded angle), the +0x40 clock resets and the tick hands off to d122c. */
typedef unsigned char u8;
struct Vecx32 { int x, y, z; };
struct hw60 { unsigned short lo : 8, hi : 8; };

extern void func_ov015_02080c00(int piece, int slot, int carried, int a);
extern void func_0203c634(int node, int slot, void *cb);
extern void func_0202f240(void *axis, int *angle, void *quat);
extern void func_ov262_020d4e6c(int node);

void func_ov262_020d4d4c(int node)
{
    int *state = *(int **)(node + 4);
    int actor = *state;
    unsigned short *hw;
    unsigned int h;
    int d;
    int angle;

    if ((unsigned short)*(int *)(*(int *)(actor + 0x3a0) + *(u8 *)(state + 0x12) * 0x24 + 0x18) == 1) {
        hw = (unsigned short *)(actor + 0x60);
        h = *hw;
        /* hw60.hi |= 0x80 -- explicit-shift form (bitfield |= adds a redundant mask) */
        *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 0x80) << 0x18) >> 0x10);
        ((struct hw60 *)(*state + 0x60))->hi &= ~1;
        func_ov015_02080c00(*(int *)(*(int *)(*state + 0x3a0)), *(u8 *)(*state + 0x3ad), 1, 0);
        *(int *)(*state + 0x3a4) = 0;
        state[0xb] = 0;
        *(u8 *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    d = 0x2000 - *(int *)(actor + 0x13c);
    state[0xd] += d / 50;
    func_0202f240(state + 0x1d, &angle, state + 3);
    state[0x10] = 0;
    func_0203c634(node, *(signed char *)(node + 0x20), func_ov262_020d4e6c);
}
