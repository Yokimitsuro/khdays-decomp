/* Return entry of an ov260 helper: the flat distance from its +0x18 anchor to the owner's +0x3a4
 * aim sets the +0x44 flight speed ((dist - 5.0) x 0.066, at least 0.3125), the +8 facing turns from
 * the rest axis to the owner's +0x3b0 aim, the owner's +0x38c link clears, bit 0 of its +0x60 high
 * byte is set and bits 2 and 7 drop, the +0x388 shape shows, the +0x48 flag and +0x40 clear, the
 * +0x28 velocity rests, +0x1c starts at the +0x390 part's position and the node moves on to 020d13ac. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { int x, y, z, w; } Quat;
typedef struct { unsigned f : 8; } B8;

extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *out);
extern void func_0202ed60(Quat *out, const Vec3 *from, const Vec3 *to);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov260_020d13ac(void);
extern const Vec3 data_02042258;
extern const Vec3 data_02041dc8;

void func_ov260_020d1260(int *node)
{
    int *state = (int *)node[1];
    Vec3 d;

    VEC_Subtract((Vec3 *)(*state + 0x3a4), (Vec3 *)state[6], &d);
    d.y = 0;
    {
        int over = func_01ff8d18(&d, &d) - 0x5000;

        state[0x11] = over * 0x88 / 0x800;
    }
    if (state[0x11] < 0x500) {
        state[0x11] = 0x500;
    }
    func_0202ed60((Quat *)(state + 2), &data_02042258, (Vec3 *)(*state + 0x3b0));
    *(int *)(*state + 0x38c) = 0;
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
    }
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(u16)((((unsigned int)hw << 0x10) >> 0x18) & ~0x84) << 0x18) >> 0x10);
    }
    ((B8 *)(*(int *)(*state + 0x388) + 8))->f |= 1;
    *((u8 *)state + 0x48) = 0;
    state[0x10] = 0;
    *(Vec3 *)(state + 10) = data_02041dc8;
    *(Vec3 *)(state + 7) = *(Vec3 *)(*(int *)(*state + 0x390) + 0x74);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov260_020d13ac);
}
