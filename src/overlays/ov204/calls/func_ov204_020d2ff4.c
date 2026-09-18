/* Charge advance of the ov204 enemy (and its byte-identical twin): the +8 velocity is the
 * +0x390 part's motion step rotated by the actor's +0xa0 orientation, the charge helper runs,
 * the target is re-acquired (the +0x38 yaw aimed at it from the +0x24 position), the +0x3c turn
 * rate is the step over 0x3000 capped at 0x200 and the +0x2c travel grows by the step. Once the
 * +0x28 busy byte clears the actor plays animation 0x12 and the tick hands off to d30e0. */
typedef unsigned char u8;
struct Vecx32 { int x, y, z; };

extern int func_ov107_020c9f48(void *part, struct Vecx32 *out);
extern void func_0202f384(void *dst, void *quat, struct Vecx32 *src);
extern void func_01ffa724(int scale, void *v, void *d);
extern void func_ov204_020d3114(int *state);
extern int func_ov107_020cab14(int actor, int mode);
extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_020050b4(int x, int z);
extern int FX_Inv(int a, int b);
extern void func_ov107_020c9264(int actor, int anim, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov204_020d30e0(int *node);

void func_ov204_020d2ff4(int *node)
{
    int *state = (int *)node[1];
    struct Vecx32 step;
    struct Vecx32 dir;
    int speed;
    int rate;

    speed = func_ov107_020c9f48(*(void **)(*state + 0x390), &step);
    func_0202f384(state + 2, (void *)(*state + 0xa0), &step);
    func_01ffa724(speed, state + 2, state + 2);
    func_ov204_020d3114(state);
    state[1] = func_ov107_020cab14(*state, 0);
    if (state[1] != 0) {
        VEC_Subtract((void *)(state[1] + 0x74), (void *)state[9], &dir);
        state[0xe] = func_020050b4(dir.x, dir.z);
    }
    rate = FX_Inv(speed, 0x3000);
    if (rate > 0x200) {
        rate = 0x200;
    }
    state[0xf] = rate;
    state[0xb] += speed;
    if (*(u8 *)state[10] != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0x12, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov204_020d30e0);
}
