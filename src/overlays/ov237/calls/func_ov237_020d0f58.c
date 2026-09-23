/* Launch of an ov237 shot: the +0x28 timer clears, bit 0 of the owner's +0x60 high byte is set and
 * bits 2 and 7 cleared, bit 0 of the +0x388 rig's +8 flags is set, the +0x2c start point takes the +8
 * point, the +0xc velocity is the +0x18 direction at 0.25 with the +0x24 speed 0.25, and the brain
 * waits on 020d1050. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned f : 8; } B8;

extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov237_020d1050(void);

void func_ov237_020d0f58(int *node)
{
    int *state = (int *)node[1];

    state[0xa] = 0;
    {
        u16 hw = *(u16 *)(*state + 0x60);

        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
    }
    {
        u16 hw = *(u16 *)(*state + 0x60);

        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~4) << 0x18) >> 0x10);
    }
    ((B8 *)(*(int *)(*state + 0x388) + 8))->f |= 1;
    *(Vec3 *)(state + 0xb) = *(Vec3 *)state[2];
    {
        u16 hw = *(u16 *)(*state + 0x60);

        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~0x80) << 0x18) >> 0x10);
    }
    func_01ffa724(0x400, (Vec3 *)(state + 6), (Vec3 *)(state + 3));
    state[9] = 0x400;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov237_020d1050);
}
