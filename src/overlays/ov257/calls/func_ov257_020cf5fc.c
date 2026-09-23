/* Strike wind-up tick of an ov257 state: the +0x54 timer accumulates the frame rate and at 0.2
 * reaction +0x408 mode 0xb fires once at the +4 point (+0x76). The +0x40 rate is the frame rate x
 * 0.6; with a nearest target (020cab14, kept in +0x60) the +0x2c orientation turns to face it
 * about data_02042264. Once the +0xc idle byte clears, animation 0x11 plays, +0x76 clears and the
 * tick hands over to func_ov257_020cf718. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[4]; } Quat;

extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern int func_ov107_020cab14(int obj, int kind);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_020050b4(int y, int x);
extern void func_0202f188(Quat *out, const Vec3 *axis, int angle);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov257_020cf718(int *node);
extern const Vec3 data_02042264;

void func_ov257_020cf5fc(int *node)
{
    int *state = (int *)node[1];
    Vec3 d;

    state[0x15] += *(int *)(node[0] + 0x2c);
    if (*((unsigned char *)state + 0x76) == 0 && state[0x15] >= 0x333) {
        func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x408), 0xb, (void *)state[1]);
        *((unsigned char *)state + 0x76) = 1;
    }
    state[0x10] = *(int *)(node[0] + 0x2c) * 30 / 50;
    state[0x18] = func_ov107_020cab14(*state, 0);
    if (state[0x18] != 0) {
        VEC_Subtract((void *)(state[0x18] + 0x74), (void *)(*state + 0x74), &d);
        func_0202f188((Quat *)(state + 0xb), &data_02042264, func_020050b4(d.x, d.z));
    }
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0x11, 0);
    *((unsigned char *)state + 0x76) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov257_020cf718);
}
