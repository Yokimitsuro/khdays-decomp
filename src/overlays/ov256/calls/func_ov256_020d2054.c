/* Aim entry of an ov256 claw: bits 2-4 of the owner's +0x60 high byte are set, the nearest live entity
 * (020cab14) becomes the +4 target and the +0x1c spin is the unit direction from the +0xc anchor to
 * its +0x190 point, its height clamped to [-0.5, 0.25] (the flat part grows by the excess over 0.75)
 * and renormalised, then scaled to 2.0. The +0x390 part takes motion 0, +0x80 rests on the vertical
 * axis, the +0x6c flag and +0x60 clear and the node moves on to 020d21d0. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020cab14(int obj, int kind);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov256_020d21d0(void);
extern const Vec3 data_02042264;

void func_ov256_020d2054(int *node)
{
    int *state = (int *)node[1];

    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x1c) << 0x18) >> 0x10);
    }
    state[1] = func_ov107_020cab14(*state, 0);
    VEC_Subtract((Vec3 *)(state[1] + 0x190), (Vec3 *)state[3], (Vec3 *)(state + 7));
    func_01ff8d18((Vec3 *)(state + 7), (Vec3 *)(state + 7));
    if (state[8] > 0x400) {
        int over = state[8] - 0x400;

        state[7] += over * (state[7] / 0xc00);
        state[9] += over * (state[9] / 0xc00);
        state[8] = 0x400;
        func_01ff8d18((Vec3 *)(state + 7), (Vec3 *)(state + 7));
    }
    if (state[8] < -0x400) {
        int over = state[8] + 0x400;

        state[7] -= over * (state[7] / 0xc00);
        state[9] -= over * (state[9] / 0xc00);
        state[8] = -0x800;
        func_01ff8d18((Vec3 *)(state + 7), (Vec3 *)(state + 7));
    }
    func_01ffa724(0x2000, (Vec3 *)(state + 7), (Vec3 *)(state + 7));
    func_ov107_020c9ee8(*(int *)(*state + 0x390), 0, 0);
    *(Vec3 *)(state + 0x20) = data_02042264;
    *((u8 *)state + 0x6c) = 0;
    state[0x18] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov256_020d21d0);
}
