/* Dash entry of the ov223 enemy: raises bit 7 of the owner's +0x60 high byte, clears the
 * owner's +0x388, clears bit 0 of the +0x60 high byte, zeroes the +0x14 velocity and +0x40,
 * and hands the tick over to func_ov223_020d4ab4. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
struct hw60 { unsigned short lo : 8, hi : 8; };

extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02041dc8;
extern void func_ov223_020d4ab4(int *node);

void func_ov223_020d4a1c(int *node)
{
    int *state = (int *)node[1];
    Vec3 zero = data_02041dc8;
    u16 flags;

    flags = *(u16 *)(*state + 0x60);
    *(u16 *)(*state + 0x60) = (u16)((flags & ~0xff00) | (((((unsigned int)flags << 0x10) >> 0x18 | 0x80) << 0x18) >> 0x10));
    *(int *)(*state + 0x388) = 0;
    ((struct hw60 *)(*state + 0x60))->hi &= ~1;
    *(Vec3 *)(state + 5) = zero;
    state[0x10] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov223_020d4ab4);
}
