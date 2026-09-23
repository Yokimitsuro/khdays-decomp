/* Throw tick of the ov237 actor: the +0x30 clock runs up at the frame rate. With nothing held
 * (+0x55 clear), the +0x3e0 shot idle and the +4 rig idle the next move is 2. Otherwise the idle pose
 * replays when the rig is idle; at 0x330 the two-handed hold (+0x55 = 2) drops to one with effects
 * 4 / 5 at the +0x42c / +0x440 hands, and from 0x28e8 the last one is thrown: the +0x3e0 shot leaves
 * the +0x42c hand toward the +0x3dc target (020d0a4c), effect 6 plays 3.5 above the +0x38 point offset
 * by data_ov237_020d1b7c turned by the +0x10 heading, and the throw sound (0x12d variant 7). */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;

extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void MTX_RotY33_(Mtx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(const Vec3 *pIn, const Mtx33 *pMtx, Vec3 *pOut);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_ov237_020d0a4c(int shot, const Vec3 *from, const Vec3 *dir);
extern void func_ov107_020c5af8(int actor, int bank, int variant, int at);
extern const short data_0203d210[];
extern const Vec3 data_ov237_020d1b7c;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov237_020cf048(int *node)
{
    int *state = (int *)node[1];
    Vec3 dir;
    Mtx33 rot;
    Vec3 pos;
    Vec3 off;

    state[0xc] += *(int *)(node[0] + 0x2c);
    if (*((u8 *)state + 0x55) == 0 && *(int *)(*(int *)(*state + 0x3e0) + 0x38c) == 0 &&
        *(u8 *)(state[1] + 0xad) == 0) {
        *(signed char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (*(u8 *)(state[1] + 0xad) == 0) {
        func_ov107_020c9264(*state, 0, 0);
    }
    if (state[0xc] >= 0x330 && *((u8 *)state + 0x55) == 2) {
        (*((u8 *)state + 0x55))--;
        func_ov107_020c0b90(*state, 4, *(Vec3 *)(*(int *)(*state + 0x42c) + 0x14), 0);
        func_ov107_020c0b90(*state, 5, *(Vec3 *)(*(int *)(*state + 0x440) + 0x14), 0);
    }
    if (state[0xc] < 0x28e8) {
        return;
    }
    if (*((u8 *)state + 0x55) != 1) {
        return;
    }
    pos = *(Vec3 *)state[0xe];
    off = data_ov237_020d1b7c;
    pos.y += 0x3800;
    {
        int idx = ANG2IDX(state[4]) * 2;

        MTX_RotY33_(&rot, data_0203d210[idx], data_0203d210[idx + 1]);
    }
    MTX_MultVec33(&off, &rot, &off);
    VEC_Add(&pos, &off, &pos);
    *((u8 *)state + 0x55) = 0;
    VEC_Subtract((Vec3 *)(*(int *)(*state + 0x3dc) + 0x190), (Vec3 *)(*(int *)(*state + 0x42c) + 0x14), &dir);
    func_01ff8d18(&dir, &dir);
    func_ov237_020d0a4c(*(int *)(*state + 0x3e0), (Vec3 *)(*(int *)(*state + 0x42c) + 0x14), &dir);
    func_ov107_020c0b90(*state, 6, pos, 0);
    func_ov107_020c5af8(*state, 0x12d, 7, state[0xe]);
}
