/* Hover setup of the ov261 enemy (and its byte-identical twin): sets bit 2 of the actor's +0x40
 * flags, resets the sub-states (+0x1c6 = 0, +0x1c7 = -1), sets bits 1-2 and clears bit 3 of the
 * +0x60 flag high byte, sets bit 0 of +0x1ae, points the state at the actor's +0x74 position and
 * the +0x384 item's +0xad busy byte, seeds the +0xc and +0x1c quaternions from the shared
 * identity, clears the +0x48 byte and installs the three hover handlers in slots 1, 0 and 2. */
typedef unsigned char u8;
struct Quat { int a, b, c, d; };
struct hw60 { unsigned short lo : 8, hi : 8; };

extern void func_0203c634(int node, int slot, void *cb);
extern const struct Quat data_020420f8;
extern void func_ov262_020d4648(int node);
extern void func_ov262_020d4458(int node);
extern void func_ov262_020d4560(int node);

void func_ov262_020d4340(int node)
{
    int *state = *(int **)(node + 4);
    unsigned short *hw;
    unsigned int h;

    *(unsigned int *)(*state + 0x40) |= 4;
    *(u8 *)(*state + 0x1c6) = 0;
    *(signed char *)(*state + 0x1c7) = -1;
    hw = (unsigned short *)(*state + 0x60);
    h = *hw;
    /* hw60.hi |= 6 -- explicit-shift form (bitfield |= adds a redundant mask) */
    *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 6) << 0x18) >> 0x10);
    ((struct hw60 *)(*state + 0x60))->hi &= ~8;
    *(unsigned short *)(*state + 0x1ae) |= 1;
    state[1] = *state + 0x74;
    state[2] = *(int *)(*state + 0x384) + 0xad;
    *(struct Quat *)(state + 3) = data_020420f8;
    *(struct Quat *)(state + 7) = *(struct Quat *)(state + 3);
    *(u8 *)(state + 0x12) = 0;
    func_0203c634(node, 1, func_ov262_020d4648);
    func_0203c634(node, 0, func_ov262_020d4458);
    func_0203c634(node, 2, func_ov262_020d4560);
}
