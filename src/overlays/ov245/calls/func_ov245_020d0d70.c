/* func_ov245_020d0d70 -- in sub-state 1: rescales the state's +0x18 direction by 0.875 into the
 * +0xc velocity, builds the rotation that turns the +0x2c2258 reference onto that direction
 * (0202ed60) into the actor's +0xa0 placement (0203c9d0) and copies the velocity to +0xf0. */
typedef struct { int x, y, z; } Vec3;

extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_0202ed60(void *out, const Vec3 *a, const Vec3 *b);
extern void func_0203c9d0(int placement, void *rotation);
extern const Vec3 data_02042258;

void func_ov245_020d0d70(int *node) {
    int *state = (int *)node[1];
    int rot[4];

    if (*(signed char *)(*state + 0x1c6) != 1) {
        return;
    }
    func_01ffa724(0xe00, (Vec3 *)(state + 6), (Vec3 *)(state + 3));
    func_0202ed60(rot, &data_02042258, (Vec3 *)(state + 6));
    func_0203c9d0(*state + 0xa0, rot);
    *(Vec3 *)(*state + 0xf0) = *(Vec3 *)(state + 3);
}
