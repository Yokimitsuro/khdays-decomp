/* Launch tick of the ov259 actor: it keeps facing its target (020cd5d4) while the +0x68 timer runs
 * up to +0x80. Each time it expires the next helper slot (+0x98) is thrown when idle: the throw
 * direction is the rest vector turned by the +0x78 heading and the helper launches from the +0x10
 * point (020d26e0). With the first throw done a d100 roll is drawn, +0x84 = 0x3fc0, the next move is
 * 2 and the node ends. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int x, y, z, w; } Quat;

extern void func_ov259_020cd5d4(int *node);
extern void func_0202f188(Quat *out, const Vec3 *axis, int angle);
extern void func_0202f384(Vec3 *out, Quat *q, const Vec3 *in);
extern void func_ov259_020d26e0(int helper, Vec3 *pos, Vec3 *dir, int heading);
extern int func_02023eb4(int n);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02042264;
extern const Vec3 data_02042258;

void func_ov259_020cf5d8(int *node)
{
    int *state = (int *)node[1];
    int expired = 0;
    Vec3 dir;
    Quat q;

    func_ov259_020cd5d4(node);
    state[0x1a] += *(int *)(node[0] + 0x2c);
    if (state[0x1a] > state[0x20]) {
        expired = 1;
    }
    if (expired == 0) {
        return;
    }
    if (state[0x26] == 0) {
        int helper = *(int *)(*state + state[0x26] * 4 + 0x388);

        if (*(int *)(helper + 0x388) == 0) {
            func_0202f188(&q, &data_02042264, state[0x1e]);
            func_0202f384(&dir, &q, &data_02042258);
            func_ov259_020d26e0(helper, (Vec3 *)state[4], &dir, state[0x1e]);
        }
    } else {
        func_02023eb4(0x65);
        state[0x21] = 0x3fc0;
        *(signed char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    state[0x1a] = 0;
    state[0x26]++;
}
