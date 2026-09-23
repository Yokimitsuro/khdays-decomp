/* Glide tick of an ov257 state: the +0x50 timer accumulates the owner's rate and the +0x5c path
 * point is resolved (func_ov257_020ccf98) into the +0x10 step. Once the +0xc idle byte clears,
 * animation 0x18 plays looped, the +0x3d0 part plays motion 0x15 and the tick hands over to
 * func_ov257_020d0150. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov257_020ccf98(int *state, int point, Vec3 *dir, int *speed);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov257_020d0150(int *node);

void func_ov257_020d00b8(int *node)
{
    int *state = (int *)node[1];
    Vec3 dir;
    int speed;

    state[0x15] += *(int *)(node[0] + 0x2c);
    func_ov257_020ccf98(state, state[0x18], &dir, &speed);
    func_01ffa724(speed, &dir, (Vec3 *)(state + 4));
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0x18, 1);
    func_ov107_020c9ee8(*(int *)(*state + 0x3d0), 0x15, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov257_020d0150);
}
