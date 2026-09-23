/* Glide tick of an ov235 state: the +0x54 timer accumulates the owner's rate and the +0x5c path
 * point is resolved (func_ov235_020cccc0) into the +0x10 step. Once bit 1 of the +0x3a8 part's +4
 * byte is set, animation 0x23 plays, the part plays motion 0x19 and the tick hands over to
 * func_ov235_020d0130. */
typedef struct { int x, y, z; } Vec3;
struct Bits4 { unsigned char b0 : 1, b1 : 1; };

extern void func_ov235_020cccc0(int *state, int point, Vec3 *dir, int *speed);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov235_020d0130(int *node);

void func_ov235_020d0094(int *node)
{
    int *state = (int *)node[1];
    Vec3 dir;
    int speed;

    state[0x15] += *(int *)(node[0] + 0x2c);
    func_ov235_020cccc0(state, state[0x17], &dir, &speed);
    func_01ffa724(speed, &dir, (Vec3 *)(state + 4));
    if (((struct Bits4 *)(*(int *)(*state + 0x3a8) + 4))->b1 == 0) {
        return;
    }
    func_ov107_020c9264(*state, 0x23, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x3a8), 0x19, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov235_020d0130);
}
