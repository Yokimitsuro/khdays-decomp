/* Swoop tick of an ov235 state: the +0x40 rate is the frame rate x 3 and the nearest target
 * (020cab14) becomes +0x5c; with one, the +0x2c orientation turns to face it and the +0x10 step is
 * the +0x3a8 part's travel (020c9f48) turned by the +0x1c orientation. Once the +0xc idle byte
 * clears, animation 0x1a plays, the part plays motion 0x14 and the tick hands over to
 * func_ov235_020d0c68. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[4]; } Quat;

extern int func_ov107_020cab14(int obj, int kind);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_020050b4(int y, int x);
extern void func_0202f188(Quat *out, const Vec3 *axis, int angle);
extern int func_ov107_020c9f48(int obj, Vec3 *out);
extern void func_0202f384(Vec3 *out, const Quat *q, const Vec3 *in);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov235_020d0c68(int *node);
extern const Vec3 data_02042264;

void func_ov235_020d0b5c(int *node)
{
    int *state = (int *)node[1];
    Vec3 v;
    Vec3 d;
    int speed;

    state[0x10] = *(int *)(node[0] + 0x2c) * 30 / 10;
    state[0x17] = func_ov107_020cab14(*state, 0);
    if (state[0x17] != 0) {
        VEC_Subtract((void *)(state[0x17] + 0x74), (void *)(*state + 0x74), &d);
        func_0202f188((Quat *)(state + 0xb), &data_02042264, func_020050b4(d.x, d.z));
        speed = func_ov107_020c9f48(*(int *)(*state + 0x3a8), &v);
        func_0202f384(&v, (Quat *)(state + 7), &v);
        func_01ffa724(speed, &v, (Vec3 *)(state + 4));
    }
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0x1a, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x3a8), 0x14, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov235_020d0c68);
}
