/* Circling tick of an ov235 state: the +0x40 rate is the frame rate x 3; with a nearest target
 * (020cab14, kept in +0x5c) the +0x2c orientation faces it (0202f188 about data_02042264) and the
 * +0x10 step goes sideways around it (the flat cross of the up axis and the direction, scaled by
 * the +0x58 side times the +0x7c speed) while climbing towards 5.0 above it (a 30th of the height
 * gap per tick). Once the +0xc idle byte clears, the owner's +0x24 hook receives note 5 of
 * data_ov235_020d24d0, animation 0x1f plays, the +0x44 timer clears, the +0x2c orientation
 * turns to the +0x68 direction (0202ed60 from data_02042258), +0x74 and +0x78 clear, bit 6 of
 * the owner's +0x60 high byte is raised, reaction +0x3c8 mode 0xf fires at the +4 point and the
 * tick hands over to func_ov235_020d0f60. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[4]; } Quat;
typedef struct { u16 lo; u16 hi; } Cmd4;

extern const Cmd4 data_ov235_020d24d0[];
extern int func_ov107_020cab14(int obj, int kind);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_020050b4(int y, int x);
extern void func_0202f188(Quat *out, const Vec3 *axis, int angle);
extern void VEC_CrossProduct(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_0202ed60(Quat *out, const Vec3 *a, const Vec3 *b);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov235_020d0f60(int *node);
extern const Vec3 data_02042264;
extern const Vec3 data_02042258;

void func_ov235_020d0d8c(int *node)
{
    int *state = (int *)node[1];
    Vec3 v;
    Vec3 d;

    state[0x10] = *(int *)(node[0] + 0x2c) * 30 / 10;
    state[0x17] = func_ov107_020cab14(*state, 0);
    if (state[0x17] != 0) {
        VEC_Subtract((void *)(state[0x17] + 0x74), (void *)(*state + 0x74), &d);
        func_0202f188((Quat *)(state + 0xb), &data_02042264, func_020050b4(d.x, d.z));
        VEC_CrossProduct(&data_02042264, &d, &v);
        func_01ff8d18(&v, &v);
        func_01ffa724(state[0x1f] * state[0x16], &v, &v);
        v.y = 0;
        *(Vec3 *)(state + 4) = v;
        state[5] = -(-0x5000 - d.y) / 30;
    }
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    {
        Cmd4 note;
        Cmd4 *p = &note;
        u16 hw;

        p->hi = data_ov235_020d24d0[5].hi;
        p->lo = data_ov235_020d24d0[5].lo;
        if (*(void (**)(int, Cmd4 *, int))(*state + 0x24) != 0) {
            (*(void (**)(int, Cmd4 *, int))(*state + 0x24))(*state, p, 4);
        }
        func_ov107_020c9264(*state, 0x1f, 0);
        state[0x11] = 0;
        func_0202ed60((Quat *)(state + 0xb), &data_02042258, (Vec3 *)(state + 0x1a));
        state[0x1d] = 0;
        hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x40) << 0x18) >> 0x10);
        state[0x1e] = 0;
    }
    func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x3c8), 0xf, (void *)state[1]);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov235_020d0f60);
}
