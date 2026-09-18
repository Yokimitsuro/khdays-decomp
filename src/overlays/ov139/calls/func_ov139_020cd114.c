/* Approach tick of the ov139 enemy (and its byte-identical twin): without a target the state
 * ends with sub-state 2; else the gap to the target beyond both +0x80 radii is measured, the
 * +0xc target yaw is the direction from the +0x4c position to the target's +0x74, the +0x14
 * velocity is the +0x390 part's motion step rotated by the actor's +0xa0 orientation and, unless
 * the gap is within the actor's +0x2d8 range but beyond 0x3000, the +0x384 item's +0xa8 byte
 * clears and the tick hands off to cd224. */
typedef unsigned char u8;
struct Vecx32 { int x, y, z; };

extern int func_ov107_020cab14(int actor, int *dist);
extern void func_0203c634(int *node, int slot, void *cb);
extern void VEC_Subtract(void *a, void *b, void *d);
extern int FX_Sqrt(int x);
extern int func_020050b4(int x, int z);
extern int func_ov107_020c9f48(void *part, struct Vecx32 *out);
extern void func_0202f384(void *dst, void *quat, struct Vecx32 *src);
extern void func_01ffa724(int scale, void *v, void *d);
extern void func_ov139_020cd224(int *node);

void func_ov139_020cd114(int *node)
{
    int *state = (int *)node[1];
    int dist;
    struct Vecx32 dir;
    struct Vecx32 step;
    int speed;
    int actor;
    int target;

    target = state[1] = func_ov107_020cab14(*state, &dist);
    if (target == 0) {
        *(u8 *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    actor = *state;
    dist = FX_Sqrt(dist) - (*(int *)(target + 0x80) + *(int *)(actor + 0x80));
    VEC_Subtract((void *)(state[1] + 0x74), (void *)state[0x13], &dir);
    state[3] = func_020050b4(dir.x, dir.z);
    speed = func_ov107_020c9f48(*(void **)(*state + 0x390), &step);
    func_0202f384(state + 5, (void *)(*state + 0xa0), &step);
    func_01ffa724(speed, state + 5, state + 5);
    if (dist < *(int *)(*state + 0x2d8) && dist > 0x3000) {
        return;
    }
    *(u8 *)(*(int *)(*state + 0x384) + 0xa8) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov139_020cd224);
}
