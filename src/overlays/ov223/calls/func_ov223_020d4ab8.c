/* Charge entry of the ov223 enemy: raises bit 0 of the owner's +0x60 high byte, copies the +4
 * point to +8, clears +0x3c and sets +0x40 to 1.0, then hands the tick over by the +0x48
 * variant: 0 to func_ov223_020d4b50, 1 to func_ov223_020d4ce0. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov223_020d4b50(int *node);
extern void func_ov223_020d4ce0(int *node);

void func_ov223_020d4ab8(int *node)
{
    int *state = (int *)node[1];
    u16 flags;

    flags = *(u16 *)(*state + 0x60);
    *(u16 *)(*state + 0x60) = (u16)((flags & ~0xff00) | (((((unsigned int)flags << 0x10) >> 0x18 | 1) << 0x18) >> 0x10));
    *(Vec3 *)(state + 2) = *(Vec3 *)state[1];
    state[0xf] = 0;
    state[0x10] = 0x1000;
    switch (state[0x12]) {
    case 0:
        func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov223_020d4b50);
        break;
    case 1:
        func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov223_020d4ce0);
        break;
    }
}
