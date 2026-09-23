/* Approach tick of the ov260 actor: the +0x20 velocity is its +0x428 part's +0x2c vector turned by
 * the +0x64 heading; the nearest live entity becomes the +0x420 target and +0x50 its goal: the target's
 * +0x190 point when farther than 5.5, else the point 8.0 short of it along the approach (+0x44), or
 * none. Once the partner holds no queued move pose 2 plays, the part takes motion 1, +0x70 and the
 * +0x7b flag clear and the node moves on to 020cdecc. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;

extern void MTX_RotY33_(Mtx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(const Vec3 *pIn, const Mtx33 *pMtx, Vec3 *pOut);
extern int func_ov107_020cab14(int obj, int kind);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov260_020cdecc(void);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov260_020cdd4c(int *node)
{
    int *state = (int *)node[1];
    Mtx33 rot;
    Vec3 d;

    {
        int idx = ANG2IDX(state[0x19]) * 2;

        MTX_RotY33_(&rot, data_0203d210[idx], data_0203d210[idx + 1]);
    }
    MTX_MultVec33((Vec3 *)(*(int *)(*state + 0x428) + 0x2c), &rot, (Vec3 *)(state + 8));
    *(int *)(*state + 0x420) = func_ov107_020cab14(*state, 0);
    if (*(int *)(*state + 0x420) != 0) {
        VEC_Subtract((Vec3 *)(*(int *)(*state + 0x420) + 0x190), (Vec3 *)state[4], &d);
        if (func_01ff8d18(&d, &d) > 0x5800) {
            state[0x14] = *(int *)(*state + 0x420) + 0x190;
        } else {
            func_01ffa724(0x8000, &d, &d);
            VEC_Subtract((Vec3 *)(*(int *)(*state + 0x420) + 0x190), &d, (Vec3 *)(state + 0x11));
            state[0x14] = (int)(state + 0x11);
        }
    } else {
        state[0x14] = 0;
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*state, 2, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x428), 1, 0);
    state[0x1c] = 0;
    *((u8 *)state + 0x7b) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov260_020cdecc);
}
