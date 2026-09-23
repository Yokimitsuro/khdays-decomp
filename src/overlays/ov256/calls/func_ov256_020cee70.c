/* Sweep tick of the ov256 actor: without a pending leash request (+0x78) the +0x10 velocity is the
 * +0x450 partner's heading (020cd054) at 3.0 and the +0x4c timer advances; the first tick stores
 * the +0xc track point in +0x1c. Until 0x13a8 an oriented box on that point (half-height 0.31,
 * half-extents growing 1.0 per 0x88 of the timer up to 5.0) strikes along (0, -1.0, 0.75) turned
 * by the +0x40 heading (020cd0e8). Once the +4 item's +0xad byte clears, a leash request without
 * +0x7c sends it to move 7; otherwise +0x7c clears and the next move is +0x74 + 2. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;
typedef struct { Vec3 pos; Vec3 axis[3]; int ext[3]; } Box;
typedef struct { Vec3 pos; int radius; } Sphere;

extern void func_ov256_020cd054(Vec3 *out, int *node, void *part);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern void MTX_RotY33_(Mtx33 *m, int sin, int cos);
extern void MTX_MultVec33(const Vec3 *v, Mtx33 *m, Vec3 *d);
extern void func_ov256_020cd0e8(int *node, Sphere *s, Box *box, int b, Vec3 *dir, int c, int d, int e);
extern void func_0203c634(int *node, int slot, void *cb);
extern const short data_0203d210[];
extern const Vec3 data_02042270;
extern const Vec3 data_02042264;
extern const Vec3 data_02042258;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov256_020cee70(int *node)
{
    int *state = (int *)node[1];
    Vec3 fwd;
    Box box;
    Mtx33 m;
    Vec3 dir;
    Vec3 out;
    unsigned int idx;

    if (state[0x1e] == 0) {
        func_ov256_020cd054(&out, node, (void *)(*(int *)(*state + 0x450) + 0x2c));
        fwd = out;
        func_01ffa724(0x3000, &fwd, (Vec3 *)(state + 4));
        state[0x13] += *(int *)(node[0] + 0x2c);
        if (*((u8 *)state + 0x69) == 0) {
            *((u8 *)state + 0x69) = 1;
            *(Vec3 *)(state + 7) = *(Vec3 *)state[3];
        }
        if (state[0x13] < 0x13a8) {
            {
                Vec3 push = { 0, -0x1000, 0xc00 };

                dir = push;
            }
            box.pos = *(Vec3 *)(state + 7);
            box.axis[0] = data_02042270;
            box.axis[1] = data_02042264;
            box.axis[2] = data_02042258;
            box.ext[1] = 0x500;
            if (state[0x13] < 0x2a8) {
                box.ext[0] = state[0x13] / 0x88 << 12;
                box.ext[2] = state[0x13] / 0x88 << 12;
            } else {
                box.ext[0] = 0x5000;
                box.ext[2] = 0x5000;
            }
            idx = ANG2IDX(state[0x10]);
            MTX_RotY33_(&m, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
            MTX_MultVec33(&dir, &m, &dir);
            func_ov256_020cd0e8(node, 0, &box, 0, &dir, 1, 0, 0);
        }
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    if (state[0x1e] != 0 && state[0x1f] == 0) {
        state[0x1e] = 0;
        *(signed char *)(*state + 0x1c7) = 7;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (state[0x1f] != 0) {
        state[0x1f] = 0;
    }
    *(signed char *)(*state + 0x1c7) = state[0x1d] + 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
