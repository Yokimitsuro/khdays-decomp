/* Approach entry of the ov298 enemy: sets the +0x50 speed to 0x900 and, with a +0xc target,
 * aims the +0x2c/+0x30 yaws at it (the facing of the +0x2c yaw is dotted against that direction
 * and discarded); one of animations 5/6 plays at random and the tick hands off to d5034. */
typedef struct { int x, y, z; } Vec3;

extern void VEC_Subtract(void *a, void *b, Vec3 *d);
extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern int VEC_DotProduct(Vec3 *a, Vec3 *b);
extern int func_020050b4(int x, int z);
extern int func_02023eb4(int range);
extern void func_ov107_020c9264(int actor, int anim, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov298_020d5034(int *node);
extern short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov298_020d4f28(int *node)
{
    int *state = (int *)node[1];
    Vec3 facing;
    Vec3 dir;
    unsigned int idx;
    int actor;

    state[0x14] = 0x900;
    if (state[3] != 0) {
        idx = ANG2IDX(state[0xb]);
        facing.x = data_0203d210[idx * 2];
        facing.y = 0;
        facing.z = data_0203d210[idx * 2 + 1];
        VEC_Subtract((void *)(state[3] + 0x74), (void *)(*state + 0x74), &dir);
        func_01ff8d18(&dir, &dir);
        VEC_DotProduct(&facing, &dir);
        state[0xb] = state[0xc] = func_020050b4(dir.x, dir.z);
    }
    actor = *state;
    func_ov107_020c9264(actor, func_02023eb4(2) + 5, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov298_020d5034);
}
