/* Bone callback of the ov243 enemy (the ov241 variant with a single joint): the joint id (the
 * +0xae byte when bit 4 of +8 is set, else 0xffff) must equal the actor's +0x3a0 id; then the
 * current 4x3/3x3 pair is taken, the subscriber's +0x44 is raised by 0x400, the joint's forward
 * heading (the -Z axis through the joint's rotation) goes to +0x3b0, and the +0x394 item is
 * placed with a pure Y rotation of that heading at (actor +0xb0, subscriber +0x44, actor +0xb8). */
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
extern const Vec3 data_0204227c;
extern const Vec3 data_02042264;

void func_ov243_020d3844(int joint)
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
    if (id == *(unsigned short *)(actor + 0x3a0)) {
        func_02016294(&m43, &m33);
        func_0202ea48(&rot, &m33);
        at = m43.t;
        *(int *)(*(int *)(actor + 0x9c) + 0x44) += 0x400;
        at.y = *(int *)(*(int *)(actor + 0x9c) + 0x44);
        func_0202f384(&fwd, &rot, &data_0204227c);
        *(int *)(actor + 0x3b0) = func_020050b4(fwd.x, fwd.z);
        func_0202f188(&rot, &data_02042264, *(int *)(actor + 0x3b0));
        at.x = *(int *)(actor + 0xb0);
        at.z = *(int *)(actor + 0xb8);
        func_0203c960((void *)(*(int *)(actor + 0x394) + 0x30));
        func_0203c9d0((void *)(*(int *)(actor + 0x394) + 0x30), &rot);
        func_0203ca30((void *)(*(int *)(actor + 0x394) + 0x30), &at);
    }
}
