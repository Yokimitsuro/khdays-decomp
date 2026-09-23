/* Glide tick of the ov235 enemy: the +0x40 rate is the owner's frame rate x 15; the +0x5c path
 * point is resolved (func_ov235_020cccc0) into a direction and a speed that give the +0x10 step.
 * Once the +0xc idle byte clears, animation 0xb plays, the +0x3a8 part plays motion 0xa and the tick
 * hands over to func_ov235_020ce938. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov235_020cccc0(int *state, int point, Vec3 *dir, int *speed);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov235_020ce938(int *node);

void func_ov235_020ce898(int *node)
{
    int *state = (int *)node[1];
    Vec3 dir;
    int speed;

    state[0x10] = *(int *)(node[0] + 0x2c) * 30 / 2;
    func_ov235_020cccc0(state, state[0x17], &dir, &speed);
    func_01ffa724(speed, &dir, (Vec3 *)(state + 4));
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0xb, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x3a8), 0xa, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov235_020ce938);
}
