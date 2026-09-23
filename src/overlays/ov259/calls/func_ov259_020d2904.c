/* Start the flight of an ov259 helper: the owner's next move is 1, +0x18 takes `dir`, +0x28 the
 * heading and the +0xc velocity is `dir` at 0.3125. The launch point (owner pose origin nudged
 * 0x10e along x) and the heading / ground-normal orientation are computed but not stored, as in
 * the original. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int x, y, z, w; } Quat;

extern void func_0202f384(Vec3 *out, const void *m, const Vec3 *in);
extern void func_0202f188(Quat *out, const Vec3 *axis, int angle);
extern void func_0202ed60(Quat *out, const Vec3 *from, const Vec3 *to);
extern void func_0202ef54(Quat *a, Quat *out, Quat *b);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern const Vec3 data_02041dc8;
extern const Vec3 data_02042264;

void func_ov259_020d2904(int *state, Vec3 *dir, int heading)
{
    Vec3 at;
    Quat yaw;
    Quat tilt;

    *(signed char *)(*state + 0x1c7) = 1;
    *(Vec3 *)(state + 6) = *dir;
    func_0202f384(&at, (void *)(*state + 0xa0), &data_02041dc8);
    at.x += 0x10e;
    state[10] = heading;
    func_0202f188(&yaw, &data_02042264, heading);
    func_0202ed60(&tilt, &data_02042264, (Vec3 *)(*state + 0x124));
    func_0202ef54(&tilt, &tilt, &yaw);
    func_01ffa724(0x500, (Vec3 *)(state + 6), (Vec3 *)(state + 3));
}
