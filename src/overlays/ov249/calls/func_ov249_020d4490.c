/* Flight tick of the ov249 enemy's leap: within 3.0 of travel (+0x24) the +0xc velocity is the +0x18
 * direction at 0.5; later, while the +0x28 progress has not passed the +0x2c range, the direction is
 * swung by up to 1.22 rad along a cosine of the progress and the progress advances by the swung
 * forward step (clamped to the range while short of it). The owner's +0x74 sphere is swept (kind 3,
 * pushed away from the owner on the ground plane): on any hit effect 8 spawns on the +0x38c partner,
 * effect 0 at the owner with reaction 0x145 mode 0xe; hitting a wall along the velocity or landing
 * (+0x17a bit 1) ends with effect 0 and mode 0x11; else the travel grows by the speed and past 21.0
 * effect 0 ends it. Every end clears the travel and hands over to 020d48a4. */
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 pos; int radius; } Sphere;
typedef struct { int m[9]; } Mtx33;
struct Bits17a { unsigned char b0 : 1, b1 : 1; };

extern void func_01ffa724(int scale, Vec3 *v, Vec3 *out);
extern int func_02020400(int a, int b);
extern void MTX_RotY33_(Mtx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(const Vec3 *pIn, const Mtx33 *pMtx, Vec3 *pOut);
extern int FX_Inv(int a, int b);
extern int func_ov107_020c8eb8(int actor, Sphere *sphere, int *out);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_ov107_020ca918(int hit, int a, int b, unsigned char kind, Vec3 *push, int z);
extern void func_ov107_020c0b90(int actor, int a, Vec3 v, int b);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern int func_01fff920(int collision, Vec3 *start, Vec3 *ray);
extern int VEC_Mag(const Vec3 *v);
extern void func_ov249_020d48a4(void);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov249_020d4490(int *node)
{
    int *state = (int *)node[1];
    Sphere sphere;
    int hits[4];
    Mtx33 mtx;
    Vec3 local;
    Vec3 dir;
    int item;
    int world;
    long i;
    long n;
    int hitAny = 0;

    world = *(int *)(*state + 4);
    if (state[9] <= 0x3000) {
        func_01ffa724(0x800, (Vec3 *)(state + 6), (Vec3 *)(state + 3));
    } else {
        int range = state[0xb];
        int progress = state[0xa];

        if (progress <= range && range != 0) {
            func_01ffa724(0x800, (Vec3 *)(state + 6), (Vec3 *)(state + 3));
            {
                int idx = ANG2IDX(data_0203d210[(func_02020400(progress << 15, range) >> 4) * 2 + 1] * 0x138c / 0x1000);

                MTX_RotY33_(&mtx, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
            }
            MTX_MultVec33((Vec3 *)(state + 3), &mtx, (Vec3 *)(state + 3));
            local.x = 0;
            local.y = 0;
            local.z = 0x800;
            MTX_MultVec33(&local, &mtx, &local);
            func_01ffa724(FX_Inv(*(int *)(node[0] + 0x2c), 0x88), &local, &local);
            if (state[0xa] < state[0xb]) {
                state[0xa] += local.z;
                if (state[0xa] > state[0xb]) {
                    state[0xa] = state[0xb];
                }
            } else {
                state[0xa] += local.z;
            }
        }
    }
    sphere = *(Sphere *)(*state + 0x74);
    n = func_ov107_020c8eb8(*(int *)(*state + 0x38c), &sphere, hits);
    for (i = 0; i < n; i++) {
        VEC_Subtract((Vec3 *)(hits[i] + 0x74), (Vec3 *)(*state + 0x74), &dir);
        dir.y = 0;
        func_01ff8d18(&dir, &dir);
        if (func_ov107_020ca918(hits[i], *state, *(int *)(*state + 0x38c), 3, &dir, 0) != 0) {
            hitAny = 1;
        }
    }
    if (hitAny) {
        func_ov107_020c0b90(*(int *)(*state + 0x38c), 8, *(Vec3 *)(*state + 0x74), 0);
        func_ov107_020c0b90(*state, 0, *(Vec3 *)(*state + 0x74), 1);
        func_ov107_020c5af8(*state, 0x145, 0xe, (void *)state[2]);
        state[9] = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov249_020d48a4);
        return;
    }
    if (func_01fff920(*(int *)(world + 0x7c), (Vec3 *)state[2], (Vec3 *)(state + 3)) != 0) {
        item = *state;
        func_ov107_020c0b90(item, 0, *(Vec3 *)(item + 0x74), 1);
        func_ov107_020c5af8(*state, 0x145, 0x11, (void *)state[2]);
        state[9] = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov249_020d48a4);
        return;
    }
    item = *state;
    if (((struct Bits17a *)(item + 0x17a))->b1 != 0) {
        func_ov107_020c0b90(item, 0, *(Vec3 *)(item + 0x74), 1);
        func_ov107_020c5af8(*state, 0x145, 0x11, (void *)state[2]);
        state[9] = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov249_020d48a4);
        return;
    }
    state[9] += VEC_Mag((Vec3 *)(state + 3));
    if (state[9] < 0x15000) {
        return;
    }
    item = *state;
    func_ov107_020c0b90(item, 0, *(Vec3 *)(item + 0x74), 1);
    state[9] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov249_020d48a4);
}
