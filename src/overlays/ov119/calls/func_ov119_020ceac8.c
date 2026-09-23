/* Reposition tick of the ov119 enemy (x3 with ov272/ov279). Every 1.0 of the +0x50 timer (fed by
 * the owner's rate) the owner is placed (c5c54) 0.94 behind the +8 target: the target's rig yaw
 * (+0x18c -> +0x20 -> +0x80, turned half a circle and converted to radians) gives the direction
 * from its +0x74 point. The timer restarts and the tick hands over to func_ov119_020cec1c. */
typedef struct { int x, y, z; } Vec3;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)
#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

extern void func_ov107_020c5c54(int owner, Vec3 *pos);
extern void func_0203c634(int *node, int slot, void *cb);
extern const short data_0203d210[];
extern void func_ov119_020cec1c(int *node);

void func_ov119_020ceac8(int *node)
{
    int *state = (int *)node[1];
    Vec3 pos;
    int target;
    int rad;
    int yaw;

    state[0x14] += *(int *)(*node + 0x2c);
    if (state[0x14] < 0x1000) {
        return;
    }
    state[0x14] = 0;
    target = state[2];
    yaw = (*(unsigned short *)(*(int *)(*(int *)(target + 0x18c) + 0x20) + 0x80) - 0x8000) & 0xffff;
    rad = (int)(((long long)yaw * 0x6487f + 0x80000) >> 20);
    pos.x = *(int *)(target + 0x74) + FX_MUL(data_0203d210[ANG2IDX(rad) * 2], 0xf00);
    pos.y = *(int *)(target + 0x78);
    pos.z = *(int *)(target + 0x7c) + FX_MUL(data_0203d210[ANG2IDX(rad) * 2 + 1], 0xf00);
    func_ov107_020c5c54(*state, &pos);
    state[0x14] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov119_020cec1c);
}
