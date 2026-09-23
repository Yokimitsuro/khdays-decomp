/* Glide tick of an ov255 state: the +0x40 rate is the owner's frame rate x 15, and the +0x5c path
 * point is resolved (func_ov255_020ccdac) into the +0x10 step. Once the +0xc idle byte clears,
 * animation 5 plays, the +0x3a4 part plays motion 4, the +0x50 timer and +0x65 flag clear and the
 * tick hands over to func_ov255_020cde10. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov255_020ccdac(int *state, int point, Vec3 *dir, int *speed);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov255_020cde10(int *node);

void func_ov255_020cdd64(int *node)
{
    int *state = (int *)node[1];
    Vec3 dir;
    int speed;

    state[0x10] = *(int *)(node[0] + 0x2c) * 30 / 2;
    func_ov255_020ccdac(state, state[0x17], &dir, &speed);
    func_01ffa724(speed, &dir, (Vec3 *)(state + 4));
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    func_ov107_020c9264(*state, 5, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x3a4), 4, 0);
    state[0x14] = 0;
    *((unsigned char *)state + 0x65) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov255_020cde10);
}
