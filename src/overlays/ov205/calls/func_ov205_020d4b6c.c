/* Approach tick of the ov204 enemy (and its byte-identical twin): without a target the state
 * ends with sub-state 2; else the +0x3c turn rate is the frame-time * 3, the +0x38 target yaw is
 * the direction from the +0x24 position to the target's +0x74, the +8 velocity is the +0x390
 * part's motion step rotated by the actor's +0xa0 orientation and, unless the target distance is
 * within the actor's +0x2d8 reach yet beyond 0x5000, the +0x384 item's +0xa8 byte is cleared and
 * the tick hands off to the next approach state. */
typedef unsigned char u8;
struct Vecx32 { int x, y, z; };

extern int func_ov107_020cab14(int actor, int *dist);
extern void func_0203c634(int *node, int slot, void *cb);
extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_020050b4(int x, int z);
extern int func_ov107_020c9f48(void *part, struct Vecx32 *out);
extern void func_0202f384(void *dst, void *quat, struct Vecx32 *src);
extern void func_01ffa724(int scale, void *v, void *d);
extern void func_ov205_020d4c84(int *node);

void func_ov205_020d4b6c(int *node)
{
    int *state = (int *)node[1];
    int dist;
    struct Vecx32 dir;
    struct Vecx32 step;
    int speed;

    state[1] = func_ov107_020cab14(*state, &dist);
    if (state[1] == 0) {
        *(u8 *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    state[0xf] = *(int *)(*node + 0x2c) * 30 / 10;
    VEC_Subtract((void *)(state[1] + 0x74), (void *)state[9], &dir);
    state[0xe] = func_020050b4(dir.x, dir.z);
    speed = func_ov107_020c9f48(*(void **)(*state + 0x390), &step);
    func_0202f384(state + 2, (void *)(*state + 0xa0), &step);
    func_01ffa724(speed, state + 2, state + 2);
    if (dist < *(int *)(*state + 0x2d8) && dist > 0x5000) {
        return;
    }
    *(u8 *)(*(int *)(*state + 0x384) + 0xa8) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov205_020d4c84);
}
