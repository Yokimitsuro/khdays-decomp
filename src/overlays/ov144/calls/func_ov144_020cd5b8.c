/* Advance tick of the ov144 enemy (and its byte-identical twin). In sub-state 3 a piece that
 * lures it sets the +0x4c lure flag and requests sub-state 4. The +0x394 item's speed is capped at
 * half the distance to the +0xc point (the facing (sin, 0, cos) of the +0x30 yaw stands in when the
 * target is reached), the +0x34 target yaw aims at it and the +0x24 velocity is the direction
 * scaled by the speed times the alignment (zero below 0xe00); in sub-state 3 an alignment below
 * 0x800 clears +0x3f4 and hands off to the facing check. Lured, reaching twice the +0x80 range
 * requests sub-state 6; otherwise, within range, the next +0x39c path node (modulo the +0x3b8
 * count) becomes the point while its +0xc charge stays at or below 0x100, else sub-state 2. */
typedef struct Vec3 { int x, y, z; } Vec3;

extern int func_ov144_020cc970(int *state, int flag);
extern int func_ov107_020c9f48(void *item, int mode);
extern void VEC_Subtract(void *a, void *b, Vec3 *d);
extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern int func_020050b4(int x, int z);
extern int VEC_DotProduct(Vec3 *a, Vec3 *b);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern void func_ov144_020cd820(int *node);
extern short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)
#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

void func_ov144_020cd5b8(int *node)
{
    int *state = (int *)node[1];
    int len;
    int speed;
    int range = *(int *)(*state + 0x80);
    int dot;
    int actor;
    unsigned int idx;
    Vec3 dir;
    Vec3 facing;

    if (*(signed char *)(*state + 0x1c6) == 3 && func_ov144_020cc970(state, 1) != 0) {
        state[0x13] = 1;
        *(unsigned char *)(*state + 0x1c7) = 4;
    }
    speed = func_ov107_020c9f48(*(void **)(*state + 0x394), 0);
    idx = ANG2IDX(state[0xc]);
    facing.x = data_0203d210[idx * 2];
    facing.y = 0;
    facing.z = data_0203d210[idx * 2 + 1];
    VEC_Subtract(state + 3, (void *)state[2], &dir);
    dir.y = 0;
    len = func_01ff8d18(&dir, &dir);
    if (len == 0) {
        dir = facing;
    }
    if (len < speed) {
        speed = len >> 1;
    }
    state[0xd] = func_020050b4(dir.x, dir.z);
    dot = VEC_DotProduct(&dir, &facing);
    if (*(signed char *)(*state + 0x1c6) == 3 && dot < 0x800) {
        *(int *)(*state + 0x3f4) = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov144_020cd820);
        return;
    }
    if (dot < 0xe00) {
        dot = 0;
    }
    func_01ffa724(FX_MUL(speed, dot), &dir, (Vec3 *)(state + 9));
    if (state[0x13] != 0) {
        if (len > range * 2) {
            return;
        }
        *(unsigned char *)(*state + 0x1c7) = 6;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (len > range) {
        return;
    }
    actor = *state;
    if (*(int *)(actor + 0x39c) != 0 && *(int *)(actor + 0x3b8) != 0) {
        state[0x11] = (state[0x11] + 1) % *(int *)(actor + 0x3b8);
        state[0x10] = *(int *)(*(int *)(*state + 0x39c) + state[0x11] * 0x10 + 0xc);
        if (state[0x10] <= 0x100) {
            *(Vec3 *)(state + 3) = *(Vec3 *)(*(int *)(*state + 0x39c) + state[0x11] * 0x10);
            return;
        }
    }
    *(unsigned char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
