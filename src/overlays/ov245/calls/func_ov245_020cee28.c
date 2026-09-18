/* func_ov245_020cee28 -- charge entry: raises bit 7 and clears bit 0 of the actor's +0x60 high
 * byte, clears bit 0 of the +0x388 item's +8 low byte, zeroes the state's +0xc vector, keeps
 * the +8 origin at +0x34, clears the +0x30 timer and installs the charge delay (020ceef0). */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
struct hw60 { unsigned short lo : 8, hi : 8; };
struct w8 { unsigned int lo : 8, rest : 24; };

extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02041dc8;
extern void func_ov245_020ceef0(void);

void func_ov245_020cee28(int *node) {
    int *state = (int *)node[1];
    Vec3 zero = data_02041dc8;

    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x80) << 0x18) >> 0x10);
    }
    ((struct hw60 *)(*state + 0x60))->hi &= ~1;
    ((struct w8 *)(*(int *)(*state + 0x388) + 8))->lo &= ~1;
    *(Vec3 *)(state + 3) = zero;
    *(Vec3 *)(state + 0xd) = *(Vec3 *)state[2];
    state[0xc] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov245_020ceef0);
}
