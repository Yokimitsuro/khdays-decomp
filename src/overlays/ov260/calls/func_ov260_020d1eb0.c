/* Launch entry of an ov260 helper: its +8 facing turns from the rest axis to the owner's +0x3a0
 * aim, bit 0 of the owner's +0x60 high byte is set, its +0x388 shape shows, bit 7 drops, the +0x28
 * velocity clears, +0x34 = 0 and +0x38 = 0xa00, +0x1c starts at the +0x38c owner's position and the
 * node moves on to 020d1fa0. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { int x, y, z, w; } Quat;
typedef struct { unsigned f : 8; } B8;

extern void func_0202ed60(Quat *out, const Vec3 *from, const Vec3 *to);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov260_020d1fa0(void);
extern const Vec3 data_02042258;
extern const Vec3 data_02041dc8;

void func_ov260_020d1eb0(int *node)
{
    int *state = (int *)node[1];

    func_0202ed60((Quat *)(state + 2), &data_02042258, (Vec3 *)(*state + 0x3a0));
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
    }
    ((B8 *)(*(int *)(*state + 0x388) + 8))->f |= 1;
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(u16)((((unsigned int)hw << 0x10) >> 0x18) & ~0x80) << 0x18) >> 0x10);
    }
    *(Vec3 *)(state + 10) = data_02041dc8;
    state[0xd] = 0;
    state[0xe] = 0xa00;
    *(Vec3 *)(state + 7) = *(Vec3 *)(*(int *)(*state + 0x38c) + 0x74);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov260_020d1fa0);
}
