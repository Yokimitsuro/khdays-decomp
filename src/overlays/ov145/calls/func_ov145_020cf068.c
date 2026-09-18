/* Charge entry of the ov144 enemy (and its byte-identical twin), gated on bit 0 of the +0x60
 * flag: clears the +0x44/+0x48/+0x4c slot, index and lure flag, takes the +0x3c timer from the
 * actor's +0x3c0 table and the +0x30/+0x34 yaws from the +0x3e8 yaw, aims the +0xc point at the
 * first +0x39c path node (and its +0xc charge) when a path and +0x3b8 anchor exist, else at the
 * +8 target with charge 0; the actor is placed at its +0x3ac spot and, when a piece lures it, the
 * yaws face the target, the lure flag is set and sub-state 7 is requested, otherwise the +0x1c9
 * fallback sub-state; the tick then hands off to a null callback. */
typedef struct Vec3 { int x, y, z; } Vec3;
struct hw60 { unsigned short lo : 8, hi : 8; };

extern void func_ov107_020c5c54(int actor, int spot);
extern int func_ov145_020ce78c(int *state, int flag);
extern void VEC_Subtract(void *a, void *b, Vec3 *d);
extern int func_020050b4(int x, int z);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov145_020cf068(int *node)
{
    int *state = (int *)node[1];
    int actor;
    int path;
    Vec3 d;

    if ((((struct hw60 *)(*state + 0x60))->lo & 1) == 0) {
        return;
    }
    state[0x11] = 0;
    state[0x12] = 0;
    state[0x13] = 0;
    state[0xf] = *(int *)(*state + state[0x12] * 4 + 0x3c0);
    state[0xc] = state[0xd] = *(int *)(*state + 0x3e8);
    actor = *state;
    path = *(int *)(actor + 0x39c);
    if (path != 0 && *(int *)(actor + 0x3b8) != 0) {
        *(Vec3 *)(state + 3) = *(Vec3 *)(path + state[0x11] * 0x10);
        state[0x10] = *(int *)(*(int *)(*state + 0x39c) + state[0x11] * 0x10 + 0xc);
    } else {
        *(Vec3 *)(state + 3) = *(Vec3 *)state[2];
        state[0x10] = 0;
    }
    func_ov107_020c5c54(*state, *state + 0x3ac);
    if (func_ov145_020ce78c(state, 0) != 0) {
        VEC_Subtract(state + 3, (void *)state[2], &d);
        state[0xc] = state[0xd] = func_020050b4(d.x, d.z);
        state[0x13] = 1;
        *(unsigned char *)(*state + 0x1c7) = 7;
    } else {
        *(signed char *)(*state + 0x1c7) = *(signed char *)(*state + 0x1c9);
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
