/* Recoil fall tick of the ov260 actor: +0x20 follows the +0x2c velocity, which takes the +0x428
 * part's +0x30 lift (height and fall speed) when it has one, and the body sweeps for hits around its
 * +0x74 position (020cd2a0 kind 4). On landing (+0x17a bit 0) the +0x54 impact point is its ground
 * point lowered by the +0x80 radius, bit 6 of the +0x60 high byte drops, it is knocked back there
 * (mode 2), effect 0xd starts there, pose 0x1c plays, +0x70 and the +0x79 / +0x7b flags clear and the
 * node moves on to 020cfa38. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;
struct Flag17a { u8 b0 : 1; };

extern void MTX_RotY33_(Mtx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(const Vec3 *pIn, const Mtx33 *pMtx, Vec3 *pOut);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov260_020cd148(int owner, int mode, int arg);
extern void func_ov260_020cd2a0(int *state, int kind, Vec3 *sphere, void *cyl, void *seg);
extern void func_0203c634(int *node, int slot, void *cb);
extern const short data_0203d210[];
extern const Vec3 data_02041dc8;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)
extern void func_ov260_020cfa38(void);

void func_ov260_020cf90c(int *node)
{
    int *state = (int *)node[1];
    int lift = *(int *)(*(int *)(*state + 0x428) + 0x30);

    *(Vec3 *)(state + 8) = *(Vec3 *)(state + 0xb);
    if (lift != 0) {
        state[0xc] = lift;
        state[9] = lift;
    }
    func_ov260_020cd2a0(state, 4, (Vec3 *)(*state + 0x74), 0, 0);
    if (!(!((struct Flag17a *)(*state + 0x17a))->b0)) {
        {
            Vec3 *land = (Vec3 *)(state + 0x15);

            *land = *(Vec3 *)(*state + 0x180);
            state[0x16] -= *(int *)(*state + 0x80);
            {
                u16 hw = *(u16 *)(*state + 0x60);
                *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
                    (((unsigned int)(u16)((((unsigned int)hw << 0x10) >> 0x18) & ~0x40) << 0x18) >> 0x10);
            }
            func_ov107_020c0b90(*state, 2, *land, 0);
            func_ov260_020cd148(*state, 0xd, (int)(state + 0x15));
            func_ov107_020c9264(*state, 0x1c, 0);
            state[0x1c] = 0;
            *((u8 *)state + 0x79) = 0;
            *((u8 *)state + 0x7b) = 0;
            func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov260_020cfa38);
        }
        return;
    }
}
