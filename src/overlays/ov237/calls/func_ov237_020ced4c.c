/* Slam tick of the ov237 actor: the +0x30 clock runs up at the frame rate. At 1.46 the pending slam
 * (+0x34 = 1) lands: the +0x48 impact point is the +0x440 hand plus data_ov237_020d1b94 turned by the
 * +0x10 heading, effect 3 and the slam sound (0x12d variant 4) play. Until 2.13 a box there (axes of the
 * world, half-extents 1.5 / 0.5 / 1.5) hits once with push data_ov237_020d1b88 (hit sound variant 5).
 * The +0x3c aim point follows the +0x3d8 partner (020cdb50); once the +4 rig is idle bit 6 of the +0x60
 * high byte clears and the next move is 2. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;
typedef struct { Vec3 pos; Vec3 axis[3]; int ext[3]; } Box;

extern void MTX_RotY33_(Mtx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(const Vec3 *pIn, const Mtx33 *pMtx, Vec3 *pOut);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov107_020c5af8(int actor, int bank, int variant, int at);
extern int func_ov237_020cdbe4(int *node, void *sphere, void *box, void *segment, Vec3 *push, int once, unsigned short effect, int kind);
extern Vec3 func_ov237_020cdb50(int *node, Vec3 *target);
extern void func_0203c634(int *node, int slot, void *cb);
extern const short data_0203d210[];
extern const Vec3 data_ov237_020d1b88;
extern const Vec3 data_ov237_020d1b94;
extern const Vec3 data_02042258;
extern const Vec3 data_02042264;
extern const Vec3 data_02042270;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov237_020ced4c(int *node)
{
    int *state = (int *)node[1];
    Vec3 hand;
    Vec3 off;
    Mtx33 rot;
    Box box;
    Vec3 push;

    state[0xc] += *(int *)(node[0] + 0x2c);
    if (state[0xc] >= 0x1760 && state[0xd] == 1) {
        hand = *(Vec3 *)(*(int *)(*state + 0x440) + 0x14);
        off = data_ov237_020d1b94;
        {
            int idx = ANG2IDX(state[4]) * 2;

            MTX_RotY33_(&rot, data_0203d210[idx], data_0203d210[idx + 1]);
        }
        MTX_MultVec33(&off, &rot, &off);
        VEC_Add(&hand, &off, &hand);
        state[0xd]--;
        func_ov107_020c0b90(*state, 3, hand, 0);
        func_ov107_020c5af8(*state, 0x12d, 4, state[0xe]);
        *(Vec3 *)(state + 0x12) = hand;
    }
    if (state[0xc] >= 0x1760 && state[0xc] < 0x2200) {
        push = data_ov237_020d1b88;
        box.pos = *(Vec3 *)(state + 0x12);
        box.axis[0] = data_02042270;
        box.axis[1] = data_02042264;
        box.axis[2] = data_02042258;
        box.ext[0] = 0x1800;
        box.ext[1] = 0x800;
        box.ext[2] = 0x1800;
        if (func_ov237_020cdbe4(node, 0, &box, 0, &push, 1, 0, 0) != 0) {
            func_ov107_020c5af8(*state, 0x12d, 5, state[0xe]);
        }
    }
    *(Vec3 *)(state + 0xf) = func_ov237_020cdb50(node, (Vec3 *)(*(int *)(*state + 0x3d8) + 0x2c));
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    {
        u16 hw = *(u16 *)(state + 0x18);

        *(u16 *)(state + 0x18) = (hw & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~0x40) << 0x18) >> 0x10);
    }
    *(signed char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
