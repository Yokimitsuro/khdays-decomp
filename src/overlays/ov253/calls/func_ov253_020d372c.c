/* Spreading-ring tick of the ov253 actor (after 020d33d8): the +0x14 clock runs up at the frame rate
 * and the +0x18 radius eases 1/30 of the way toward 12.0 each tick. The +4 rig's particles (+0x90
 * array of 0x38-byte entries, +0x8c count) are spread evenly on the ring around the +8 point at the
 * +0xc height, each scaled by 1 - clock/4.0 (not below 0). When the owner's +0x50 mode is 1 an upright
 * cylinder of the ring's radius (flag set) at the +8 point sweeps the +0x388 body's hits, and every hit
 * the body accepts (020cceb0) gets a kind-3 hit of strength 0x10. After 4.0 the node ends. */
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 pos; Vec3 axis[3]; int radius; int flag; } Cylinder;

extern int FX_Inv(int a, int b);
extern int func_02020400(int a, int b);
extern int func_ov107_020c8fd0(int actor, void *box, int *out);
extern int func_ov253_020cceb0(int item, int hit);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, const Vec3 *push, int z);
extern void func_0203c640(int *node);
extern const short data_0203d210[];
extern const Vec3 data_02042270;
extern const Vec3 data_02042258;
extern const Vec3 data_02042264;
extern const Vec3 data_02041dc8;

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

static inline unsigned short FX_RadToIdx(int rad)
{
    return (unsigned short)((0x28BE60DB9391LL * rad + 0x80000000000LL) >> 44);
}

void func_ov253_020d372c(int *node)
{
    int *state = (int *)node[1];
    int inv;
    unsigned short idx;
    int i;
    char *entry;
    int n;

    state[5] += *(int *)(node[0] + 0x2c);
    state[6] += (0xc000 - state[6]) / 30;
    inv = 0x1000 - FX_Inv(state[5], 0x4000);
    if (inv < 0) {
        inv = 0;
    }
    for (i = 0; i < *(int *)(state[1] + 0x8c); i++) {
        entry = *(char **)(state[1] + 0x90) + i * 0x38;
        idx = FX_RadToIdx(func_02020400(i * 0x6488, *(int *)(state[1] + 0x8c)));
        *(int *)(entry + 0x2c) = state[2] + FX_Mul(data_0203d210[(idx >> 4) << 1], state[6]);
        *(int *)(entry + 0x30) = state[3];
        idx = FX_RadToIdx(func_02020400(i * 0x6488, *(int *)(state[1] + 0x8c)));
        *(int *)(entry + 0x34) = state[4] + FX_Mul(data_0203d210[((idx >> 4) << 1) + 1], state[6]);
        *(int *)entry = inv;
    }
    if (*(int *)(*state + 0x50) == 1) {
        int hits[4];
        Cylinder cyl = {0};
        Vec3 d;

        cyl.pos = *(Vec3 *)(state + 2);
        cyl.axis[0] = data_02042270;
        cyl.axis[1] = data_02042258;
        cyl.axis[2] = data_02042264;
        cyl.radius = state[6];
        cyl.flag = 1;
        n = func_ov107_020c8fd0(*(int *)(*state + 0x388), &cyl, hits);
        for (i = 0; i < n; i++) {
            if (func_ov253_020cceb0(*(int *)(*state + 0x388), hits[i]) != 0) {
                VEC_Subtract((Vec3 *)(hits[i] + 0x74), &cyl.pos, &d);
                d.y = 0;
                func_01ff8d18(&d, &d);
                func_01ffa724(0x1000, &d, &d);
                func_ov107_020ca918(hits[i], *state, *(int *)(*state + 0x388), 3, &data_02041dc8, 0x10);
            }
        }
    }
    if (state[5] < 0x4000) {
        return;
    }
    func_0203c640(node);
}
