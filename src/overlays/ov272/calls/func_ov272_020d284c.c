/* Grab approach finish of the ov272 enemy (x3 with ov272/ov279). The owner is set 0.94 behind the
 * +8 target (its rig yaw turned half a circle), effect 0 spawns there and reaction 0x121 mode 5
 * fires at it; the owner then faces the target from the +0x4c point, takes the target's +0x74
 * position as its own point, the +0x50 timer restarts and the tick hands over to the grab attempt
 * (func_ov272_020d29f0). */
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[4]; } Quat;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)
#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

extern void func_ov107_020c0b90(int actor, int a, Vec3 v, int b);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0203cd7c(int *dst, const Vec3 *a, const Vec3 *b, const void *c);
extern void func_0202ea48(void *dst, const int *src);
extern void func_0203c634(int *node, int slot, void *cb);
extern const short data_0203d210[];
extern const Vec3 data_02042264;
extern void func_ov272_020d29f0(int *node);

void func_ov272_020d284c(int *node)
{
    int *state = (int *)node[1];
    int mtx[9];
    Vec3 pos;
    int target = state[2];
    Vec3 *tpos = (Vec3 *)(target + 0x74);
    int yaw = (*(unsigned short *)(*(int *)(*(int *)(target + 0x18c) + 0x20) + 0x80) - 0x8000) & 0xffff;
    int rad = (int)(((long long)yaw * 0x6487f + 0x80000) >> 20);

    pos.x = tpos->x + FX_MUL(data_0203d210[ANG2IDX(rad) * 2], 0x1680);
    pos.y = tpos->y;
    pos.z = tpos->z + FX_MUL(data_0203d210[ANG2IDX(rad) * 2 + 1], 0x1680);
    func_ov107_020c0b90(*state, 0, pos, 0);
    func_ov107_020c5af8(*state, 0x167, 5, &pos);
    {
        func_0203cd7c(mtx, tpos, (Vec3 *)state[0x13], &data_02042264);
        func_0202ea48(state + 7, mtx);
        *(Quat *)(state + 3) = *(Quat *)(state + 7);
        *(Vec3 *)(state + 0x1d) = *tpos;
    }
    state[0x14] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov272_020d29f0);
}
