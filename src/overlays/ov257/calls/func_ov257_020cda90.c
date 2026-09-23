/* Take-off tick of an ov257 state: the +0x40 rate follows the frame rate and the nearest target
 * (020cab14) becomes +0x60; without one sub-state 2 is requested. Otherwise the path point is
 * resolved (func_ov257_020ccf98) into the +0x10 step and, once the +0xc idle byte clears, animation
 * 2 and the +0x3d0 part's motion 1 play looped, +0x78 and +0x44 clear and the tick hands over to
 * func_ov257_020cdb88. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020cab14(int obj, int kind);
extern void func_ov257_020ccf98(int *state, int point, Vec3 *dir, int *speed);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov257_020cdb88(int *node);

void func_ov257_020cda90(int *node)
{
    int *state = (int *)node[1];
    Vec3 dir;
    int speed;

    state[0x10] = *(int *)(node[0] + 0x2c) * 30 / 30;
    state[0x18] = func_ov107_020cab14(*state, 0);
    if (state[0x18] == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    func_ov257_020ccf98(state, state[0x18], &dir, &speed);
    func_01ffa724(speed, &dir, (Vec3 *)(state + 4));
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    func_ov107_020c9264(*state, 2, 1);
    func_ov107_020c9ee8(*(int *)(*state + 0x3d0), 1, 1);
    *((unsigned char *)state + 0x78) = 0;
    state[0x11] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov257_020cdb88);
}
