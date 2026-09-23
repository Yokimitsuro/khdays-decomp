/* Circle tick of the ov260 actor: the +0x20 velocity is its +0x428 part's +0x2c vector turned by the
 * +0x64 heading and the body sweeps for hits (020cd2a0 kind 3). Once the partner holds no queued
 * move the circle count (+0x74) grows and a new side heading (+0x6c) is rolled 35-70 degrees left or
 * right of +0x64; the landing point (+0x14) is the target's +0x190 point stepped back 4.0 along it
 * (2.0 from the fifth circle), pushed off the scene's walls within the body radius, the recoil entry
 * is armed (+0xc = 020cebe4) and the node moves on to 020cf484. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;

extern void MTX_RotY33_(Mtx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(const Vec3 *pIn, const Mtx33 *pMtx, Vec3 *pOut);
extern void func_ov260_020cd2a0(int *state, int kind, void *sphere, void *cyl, void *seg);
extern int func_02023eb4(int n);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern int func_01fff948(int walls, Vec3 *at, Vec3 *dir, int radius);
extern void func_01ffd144(int plane, Vec3 *in, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov260_020cebe4(void);
extern void func_ov260_020cf484(void);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov260_020ce9d4(int *node)
{
    int *state = (int *)node[1];
    Mtx33 rot;
    Vec3 off;
    int scene;
    int hit;

    {
        int idx = ANG2IDX(state[0x19]) * 2;

        MTX_RotY33_(&rot, data_0203d210[idx], data_0203d210[idx + 1]);
    }
    MTX_MultVec33((Vec3 *)(*(int *)(*state + 0x428) + 0x2c), &rot, (Vec3 *)(state + 8));
    func_ov260_020cd2a0(state, 3, 0, 0, 0);
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    scene = *(int *)(*state + 4);
    state[0x1d]++;
    if (func_02023eb4(2) != 0) {
        int r = func_02023eb4(0x1923) + (hit - hit);

        state[0x1b] = state[0x19] - 0x3244 + r;
    } else {
        int r = func_02023eb4(0x1923) - 0x1922;

        state[0x1b] = state[0x19] + 0x3244 + r;
    }
    {
        int idx = ANG2IDX(state[0x1b]) * 2;

        off.x = data_0203d210[idx];
        off.y = 0;
        off.z = data_0203d210[idx + 1];
    }
    func_01ffa724(state[0x1d] < 5 ? -0x4000 : -0x2000, &off, &off);
    hit = func_01fff948(*(int *)(scene + 0x7c), (Vec3 *)(*(int *)(*state + 0x420) + 0x190), &off,
                        *(int *)(*state + 0x80));
    if (hit != 0) {
        func_01ffd144(*(int *)(hit + 0xc), &off, &off);
    }
    VEC_Add((Vec3 *)(*(int *)(*state + 0x420) + 0x190), &off, (Vec3 *)(state + 5));
    state[3] = (int)func_ov260_020cebe4;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov260_020cf484);
}
