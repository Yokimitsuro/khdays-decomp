/* Swoop tick of the ov146 enemy. With a +0x3b4 target the +0x2c yaw faces its +0x190 point from the
 * owner's +0xb0. The swoop runs while the +0x34 distance is below the +0x38 length (ending it
 * requests sub-state 2): the +0x4c sway scales a cosine of the progress into the swing angle, and
 * the climb follows a sine of five times the progress (0.1 to 0.43). A wall contact (+0x17a bit 1)
 * reflects the reversed swung heading about the owner's +0x114 contact normal into a new +0x30
 * heading and stops the sway. The +0x10 velocity is the heading times the climb, turned by the swing
 * angle, and the distance advances by the swung forward step of the frame. */
typedef struct Vec3 { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;
struct Bits17a { unsigned char bit0 : 1, bit1 : 1; };

extern void VEC_Subtract(Vec3 *a, Vec3 *b, Vec3 *d);
extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern int func_020050b4(int x, int z);
extern int func_02020400(int num, int den);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern int VEC_DotProduct(Vec3 *a, Vec3 *b);
extern void MTX_RotY33_(Mtx33 *m, int sin, int cos);
extern void MTX_MultVec33(const Vec3 *v, Mtx33 *m, Vec3 *d);
extern void func_0203c634(int *node, int slot, void *cb);
extern short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)
#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

void func_ov146_020cd3b4(int *node)
{
    int *state = (int *)node[1];
    Vec3 d;
    Mtx33 mtx;
    Vec3 v;
    Vec3 n;
    Vec3 neg;
    Vec3 refl;
    Vec3 back;
    int t;
    int len;
    int swing;
    int lift;
    unsigned int idx;

    if (*(int *)(*state + 0x3b4) != 0) {
        VEC_Subtract((Vec3 *)(*(int *)(*state + 0x3b4) + 0x190), (Vec3 *)(*state + 0xb0), &d);
        func_01ff8d18(&d, &d);
        state[0xb] = func_020050b4(d.x, d.z);
    }
    len = state[0xe];
    t = state[0xd];
    if (t < len && len != 0) {
        swing = state[0x13] * (data_0203d210[(func_02020400(t << 15, len) >> 4) * 2 + 1] * 0x138c / 0x1000);
        lift = FX_MUL(data_0203d210[((func_02020400((t * 5) << 12, len) + 0x3000) >> 4) * 2] * 0x500 / 0x1000 + 0x100,
                      0x1000);
        if (((struct Bits17a *)(*state + 0x17a))->bit1 != 0) {
            n = *(Vec3 *)(*state + 0x114);
            idx = ANG2IDX(state[0x13] * 0x138c + state[0xc]);
            back.x = data_0203d210[idx * 2];
            back.y = 0;
            back.z = data_0203d210[idx * 2 + 1];
            func_01ffa724(-0x1000, &back, &neg);
            func_01ffa724(VEC_DotProduct(&neg, &n) << 1, &n, &refl);
            VEC_Subtract(&refl, &neg, &refl);
            func_01ff8d18(&refl, &back);
            state[0xc] = func_020050b4(back.x, back.z);
            state[0x13] = 0;
        }
        idx = ANG2IDX(state[0xc]);
        v.x = data_0203d210[idx * 2];
        v.y = 0;
        v.z = data_0203d210[idx * 2 + 1];
        func_01ffa724(lift, &v, (Vec3 *)(state + 4));
        idx = ANG2IDX(swing);
        MTX_RotY33_(&mtx, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
        MTX_MultVec33((Vec3 *)(state + 4), &mtx, (Vec3 *)(state + 4));
        v.z = lift * *(int *)(node[0] + 0x2c) / 0x88;
        v.x = 0;
        v.y = 0;
        MTX_MultVec33(&v, &mtx, &v);
        state[0xd] += v.z < 0 ? -v.z : v.z;
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
