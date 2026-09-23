/* Glide tick of an ov257 state: the +0x5c path point is resolved (func_ov257_020ccf98) into the
 * +0x10 step. Once the +0xc idle byte clears, animation 0x1b and the +0x3d0 part's motion 0x18 play
 * looped, bit 6 of the owner's +0x60 high byte clears and the tick hands over to
 * func_ov257_020d085c. */
typedef struct { int x, y, z; } Vec3;
struct hw60 { unsigned short lo : 8, hi : 8; };

extern void func_ov257_020ccf98(int *state, int point, Vec3 *dir, int *speed);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov257_020d085c(int *node);

void func_ov257_020d07a8(int *node)
{
    int *state = (int *)node[1];
    Vec3 dir;
    int speed;

    func_ov257_020ccf98(state, state[0x18], &dir, &speed);
    func_01ffa724(speed, &dir, (Vec3 *)(state + 4));
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0x1b, 1);
    func_ov107_020c9ee8(*(int *)(*state + 0x3d0), 0x18, 1);
    ((struct hw60 *)(*state + 0x60))->hi &= ~0x40;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov257_020d085c);
}
