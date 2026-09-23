/* Jump tick of an ov257 state: the +0x40 rate clears, the +0x10 step heads for the +0x60 target
 * (func_ov257_020ccf98) plus the +0x64 velocity, whose height falls by 3/64 per tick; on the
 * ground (+0x17a bit 0) the horizontal velocity clears. Once falling within 12.0 of the floor
 * (+0x13c), animation 0x1e plays, the +0x3d0 part plays motion 0x1b, +0x44, +0x73 and +0x72 clear
 * and the tick hands over to func_ov257_020d1f00. */
typedef struct { int x, y, z; } Vec3;
struct Bits17a { unsigned char b0 : 1; };

extern int func_ov257_020ccf98(int *state, int target, Vec3 *dir, int *speed);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const void *a, const void *b, void *out);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov257_020d1f00(int *node);

void func_ov257_020d1e24(int *node)
{
    int *state = (int *)node[1];
    Vec3 dir;
    int speed;

    state[0x10] = 0;
    func_ov257_020ccf98(state, state[0x18], &dir, &speed);
    func_01ffa724(speed, &dir, (Vec3 *)(state + 4));
    VEC_Add(state + 4, state + 0x19, state + 4);
    state[0x1a] -= 0xc0;
    if (((struct Bits17a *)(*state + 0x17a))->b0) {
        state[0x19] = 0;
        state[0x1b] = 0;
    }
    if (state[0x1a] >= 0 || *(int *)(*state + 0x13c) >= 0xc000) {
        return;
    }
    func_ov107_020c9264(*state, 0x1e, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x3d0), 0x1b, 0);
    state[0x11] = 0;
    *((unsigned char *)state + 0x73) = 0;
    *((unsigned char *)state + 0x72) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov257_020d1f00);
}
