/* Bone callback of the ov241 enemy (x3: ov241/242/243), run while the model's joints are
 * drawn: the joint id (the +0xae byte when bit 4 of +8 is set, else 0xffff) is compared with
 * the actor's three ids at +0x3ac/+0x3ae/+0x3b0. The first id takes the current 4x3/3x3 pair,
 * places the +0x38c item at the joint, extracts the joint's forward heading (world Z through
 * the joint's rotation) into +0x3bc, raises the subscriber's +0x44 by 0x400 and places the
 * +0x3a0 item with a pure Y rotation of that heading at (actor +0xb0, subscriber +0x44, actor
 * +0xb8). The other two ids only place the +0x390 / +0x394 items at the joint. */
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

void func_ov241_020cfc04(int joint)
{
    int actor = *(int *)(*(int *)(joint + 4) + 0x2c);
    MtxFx43 m43;
    MtxFx33 m33;
    Quat rot;
    Vec3 at;
    Vec3 fwd;
    int sel;
    unsigned short id;

    if ((*(int *)(joint + 8) & 0x10) != 0) {
        sel = *(unsigned char *)(joint + 0xae);
    } else {
        sel = -1;
    }
    id = sel;
    if (id == *(unsigned short *)(actor + 0x3ac)) {
        func_02016294(&m43, &m33);
        func_0202ea48(&rot, &m33);
        at = m43.t;
        *(int *)(*(int *)(actor + 0x9c) + 0x44) += 0x400;
        at.y = *(int *)(*(int *)(actor + 0x9c) + 0x44);
        func_0203c960((void *)(*(int *)(actor + 0x38c) + 0x30));
        func_0203ca30((void *)(*(int *)(actor + 0x38c) + 0x30), &m43.t);
        func_0202f384(&fwd, &rot, &data_02042258);
        *(int *)(actor + 0x3bc) = func_020050b4(fwd.x, fwd.z);
        func_0202f188(&rot, &data_02042264, *(int *)(actor + 0x3bc));
        at.x = *(int *)(actor + 0xb0);
        at.z = *(int *)(actor + 0xb8);
        func_0203c960((void *)(*(int *)(actor + 0x3a0) + 0x30));
        func_0203c9d0((void *)(*(int *)(actor + 0x3a0) + 0x30), &rot);
        func_0203ca30((void *)(*(int *)(actor + 0x3a0) + 0x30), &at);
        return;
    }
    if (id == *(unsigned short *)(actor + 0x3ae)) {
        func_02016294(&m43, &m33);
        func_0203c960((void *)(*(int *)(actor + 0x390) + 0x30));
        func_0203ca30((void *)(*(int *)(actor + 0x390) + 0x30), &m43.t);
        return;
    }
    if (id == *(unsigned short *)(actor + 0x3b0)) {
        func_02016294(&m43, &m33);
        func_0203c960((void *)(*(int *)(actor + 0x394) + 0x30));
        func_0203ca30((void *)(*(int *)(actor + 0x394) + 0x30), &m43.t);
    }
}
