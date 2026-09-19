/* Spawn wind-up tick of the ov226 enemy. Losing the target (ov226 1330 below zero) ends the
 * action. The +0x5c timer accumulates the owner's rate; once it reaches 0x17e8 (and only once,
 * +0x75) two children are launched from the point (0, -0.5, 1.0) x 0x11ae turned by the +0x50
 * heading (data_02042264 axis) from the +0x3ac body's +0x20 point, lifted to the owner's +0x78
 * less its +0x13c, pulled 1.75 back along the heading, with the heading's sine/cosine as the
 * facing and data_02042258 turned by the heading as the direction; the step between them is
 * 2.0 along the heading. Each +0x3ec child gets mode 1 (0 with a target), the point, the facing
 * and the direction (ov226 3eb4). The owner is then sent mode 2 with the zero vector, flagged
 * when there is no target, and reaction 0x14c mode 7 fires at the +8 point. Otherwise, once
 * the +4 owner's +0xad byte clears, sub-state 2 is requested and the action ends. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { int q[4]; } Quat;
enum { SPAWN_FAN = 0, SPAWN_AIM = 1 };
struct Ov226Family { char pad[0x3ec]; int aChildren[4]; };

extern int func_ov226_020d1330(int *node, Vec3 *dir);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_0202f188(Quat *out, const Vec3 *axis, int angle);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_0202f384(Vec3 *out, const Quat *q, const Vec3 *in);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov226_020d3eb4(int self, int mode, Vec3 at, Vec3 facing, Vec3 dir);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 v, u8 flag);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern const Quat data_020420f8;
extern const Vec3 data_02041dc8;
extern const Vec3 data_02042258;
extern const Vec3 data_02042264;
extern short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov226_020d2930(int *node)
{
    int *state = (int *)node[1];
    Quat qHeading;
    Quat qSpread;
    Vec3 vAt;
    Vec3 vStep;
    Vec3 vDir;
    Vec3 vFacing;
    Vec3 vChildDir;
    Vec3 vZero;
    int n;
    long i;
    int bNoTarget;
    unsigned int idx;

    if (func_ov226_020d1330(node, 0) < 0) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    state[0x17] += *(int *)(*node + 0x2c);
    if (*(u8 *)((char *)state + 0x75) == 0 && state[0x17] >= 0x17e8) {
        qSpread = data_020420f8;
        vZero = data_02041dc8;
        vStep = data_02041dc8;
        vDir = data_02042258;
        bNoTarget = state[0x1e] != 0 ? SPAWN_FAN : SPAWN_AIM;
        idx = ANG2IDX(state[0x14]);
        vFacing.x = data_0203d210[idx * 2];
        vFacing.y = 0;
        vFacing.z = data_0203d210[idx * 2 + 1];
        func_0202f188(&qHeading, &data_02042264, state[0x14]);
        vAt.x = 0;
        vAt.y = -0x800;
        vAt.z = 0x1000;
        func_01ffa724(0x11ae, &vAt, &vAt);
        func_0202f384(&vAt, &qHeading, &vAt);
        VEC_Add(&vAt, (Vec3 *)(*(int *)(*(int *)(*state + 0x3ac)) + 0x20), &vAt);
        vAt.y = *(int *)(*state + 0x78) - *(int *)(*state + 0x13c);
        vStep.x = 0x1c00;
        vStep.y = 0;
        vStep.z = 0;
        func_0202f384(&vStep, &qHeading, &vStep);
        VEC_Subtract(&vAt, &vStep, &vAt);
        func_01ffa724(0x2000, &vStep, &vStep);
        n = 2;
        for (i = 0; i < n; i++) {
            func_0202f384(&vChildDir, &qHeading, &vDir);
            func_ov226_020d3eb4(((struct Ov226Family *)*state)->aChildren[i], bNoTarget, vAt, vFacing, vChildDir);
            func_0202f384(&vDir, &qSpread, &vDir);
            VEC_Add(&vAt, &vStep, &vAt);
        }
        func_ov107_020c0b90(*state, 2, vZero, state[0x1e] == 0);
        func_ov107_020c5af8(*state, 0x14c, 7, (void *)state[2]);
        *(u8 *)((char *)state + 0x75) = 1;
        return;
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    *(u8 *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
