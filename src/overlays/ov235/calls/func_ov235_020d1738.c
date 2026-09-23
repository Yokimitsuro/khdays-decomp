/* Turn tick of an ov235 state: the nearest target (020cab14) becomes +0x5c and, when there is one,
 * the +0x2c orientation turns to face it (0202f188 about data_02042264). The +0x40 rate is the
 * frame rate x 3; once the +0xc idle byte clears, animation 0x1d plays, the +0x3a8 part plays
 * motion 0x16 and the tick hands over to func_ov235_020d1810. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[4]; } Quat;

extern int func_ov107_020cab14(int obj, int kind);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_020050b4(int y, int x);
extern void func_0202f188(Quat *out, const Vec3 *axis, int angle);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov235_020d1810(int *node);
extern const Vec3 data_02042264;

void func_ov235_020d1738(int *node)
{
    int *state = (int *)node[1];
    Vec3 d;

    state[0x17] = func_ov107_020cab14(*state, 0);
    if (state[0x17] != 0) {
        VEC_Subtract((void *)(state[0x17] + 0x74), (void *)(*state + 0x74), &d);
        func_0202f188((Quat *)(state + 0xb), &data_02042264, func_020050b4(d.x, d.z));
    }
    state[0x10] = *(int *)(node[0] + 0x2c) * 30 / 10;
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0x1d, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x3a8), 0x16, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov235_020d1810);
}
