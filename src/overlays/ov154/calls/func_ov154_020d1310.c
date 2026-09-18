/* Facing update of the ov153 enemy (x3: ov153/154/155): unless the actor carries bit 1 of its
 * +0x1c4 flags, the +0x10 heading eases towards the +0x14 target at the +0x20 rate; the heading
 * becomes a quaternion about the world Y axis, is multiplied by the quaternion that turns Y onto
 * the actor's +0x124 up vector, and the product goes to the actor's +0xa0 orientation. */
struct Vec3 { int x, y, z; };
struct Quat { int a, b, c, d; };

extern int func_0203d040(int cur, int target, int rate, int mode);
extern void func_0202f188(struct Quat *out, const struct Vec3 *axis, int angle);
extern void func_0202ed60(struct Quat *out, const struct Vec3 *fwd, struct Vec3 *dir);
extern void func_0202ef54(struct Quat *out, const struct Quat *a, const struct Quat *b);
extern void func_0203c9d0(int dst, struct Quat *src);
extern const struct Vec3 data_02042264;

void func_ov154_020d1310(int node)
{
    int *state = *(int **)(node + 4);
    struct Quat qUp;
    struct Quat qHeading;

    if ((*(unsigned char *)(*state + 0x1c4) & 2) == 0) {
        state[4] = func_0203d040(state[4], state[5], state[8], 0);
    }
    func_0202f188(&qHeading, &data_02042264, state[4]);
    func_0202ed60(&qUp, &data_02042264, (struct Vec3 *)(*state + 0x124));
    func_0202ef54(&qUp, &qUp, &qHeading);
    func_0203c9d0(*state + 0xa0, &qUp);
}
