/* Bone callback of the ov291 enemy, run while the model's joints are drawn. When the joint id (the
 * +0xae byte when bit 4 of +8 is set, else 0xffff) is the actor's +0x39c head joint: takes the
 * joint's 4x3/3x3 pair, lifts the subscriber's +0x44 height by 0x200 and uses it as the Y of the
 * joint position, tilts the joint rotation by the overlay's quaternion and keeps only its yaw
 * (heading of the rotated world Z), places the +0x398 item there with that yaw, re-centres the
 * +0x38c item at (x, actor +0xb4, z), copies its placement to the first +0x390 item, and clears
 * the joint's +0x24 word and +0x92 byte. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } MtxFx33;
typedef struct { int m[9]; Vec3 t; } MtxFx43;
typedef struct { int a, b, c, d; } Quat;

extern void func_02016294(MtxFx43 *m43, MtxFx33 *m33);
extern void func_0202ea48(Quat *out, MtxFx33 *m33);
extern void func_0203c960(void *transform);
extern void func_0203ca30(void *transform, const Vec3 *translation);
extern void func_0203c9d0(void *transform, Quat *rotation);
extern void func_0202f384(Vec3 *out, Quat *rotation, const Vec3 *in);
extern int func_020050b4(int x, int z);
extern void func_0202f188(Quat *out, const Vec3 *axis, int angle);
extern const Vec3 data_02042258;
extern const Vec3 data_02042264;
extern const Quat data_ov291_020cd604;
extern void func_0202ef54(Quat *out, Quat *a, const Quat *b);
extern void func_0203ca14(void *transform, int x, int y, int z);
typedef struct { int w[11]; } SrtTransform;

void func_ov291_020cbfc4(char *joint)
{
    char *actor = *(char **)(*(char **)(joint + 4) + 0x2c);
    MtxFx43 m43;
    MtxFx33 m33;
    Quat rot;
    Vec3 at;
    Vec3 fwd;
    Quat tilt;
    int sel;

    if ((*(int *)(joint + 8) & 0x10) != 0) {
        sel = *(unsigned char *)(joint + 0xae);
    } else {
        sel = -1;
    }
    if (*(unsigned short *)(actor + 0x39c) != sel) {
        return;
    }
    tilt = data_ov291_020cd604;
    func_02016294(&m43, &m33);
    func_0202ea48(&rot, &m33);
    at = m43.t;
    *(int *)(*(char **)(actor + 0x9c) + 0x44) += 0x200;
    at.y = *(int *)(*(char **)(actor + 0x9c) + 0x44);
    func_0202ef54(&rot, &rot, &tilt);
    func_0202f384(&fwd, &rot, &data_02042258);
    func_0202f188(&rot, &data_02042264, func_020050b4(fwd.x, fwd.z));
    func_0203c960(*(char **)(actor + 0x398) + 0x30);
    func_0203c9d0(*(char **)(actor + 0x398) + 0x30, &rot);
    func_0203ca30(*(char **)(actor + 0x398) + 0x30, &at);
    func_0203c960(*(char **)(actor + 0x38c) + 0x10);
    func_0203ca14(*(char **)(actor + 0x38c) + 0x10, at.x, *(int *)(actor + 0xb4), at.z);
    *(SrtTransform *)(*(char **)(*(char **)(actor + 0x390)) + 0x10) = *(SrtTransform *)(*(char **)(actor + 0x38c) + 0x10);
    *(int *)(joint + 0x24) = 0;
    *(unsigned char *)(joint + 0x92) = 0;
}
