/* Per-frame update of an ov259 helper: move 3 (latch) holds it free (+0x39c = 1) and move 4
 * releases it. While held to its owner the helper follows the owner's +0x40c bone (position at +0x14,
 * rotation at +4; the turn from the rest axis is composed but unused), then the base update runs
 * (020c6980) and the +0xa0 pose is copied into the +0x390 model and on to the +0x38c shape. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int x, y, z, w; } Quat;
typedef struct { int w[11]; } Pose;

extern void func_ov107_020c5c54(char *actor, Vec3 *at);
extern void func_0202ed60(Quat *out, const Vec3 *from, const Vec3 *to);
extern void func_0202ef54(Quat *out, const Quat *a, const Quat *b);
extern void func_0203c9d0(char *srt, Quat *q);
extern void func_ov107_020c6980(char *self, int arg);
extern const Vec3 data_02042270;
extern const Vec3 data_02042264;

void func_ov259_020d1ad4(char *self, int arg)
{
    char *bone = 0;
    Vec3 axis;
    Quat q;

    if (*(signed char *)(self + 0x1c6) == 3) {
        *(int *)(self + 0x39c) = 1;
    }
    if (*(signed char *)(self + 0x1c6) == 4) {
        *(int *)(self + 0x39c) = 0;
    }
    if (*(int *)(self + 0x39c) == 0) {
        bone = *(char **)(*(char **)(self + 0x394) + 0x40c);
        axis = data_02042270;
    }
    if (bone != 0) {
        func_ov107_020c5c54(self, (Vec3 *)(bone + 0x14));
        func_0202ed60(&q, &data_02042264, &axis);
        func_0202ef54(&q, (Quat *)(bone + 4), &q);
        func_0203c9d0(self + 0xa0, (Quat *)(bone + 4));
    }
    func_ov107_020c6980(self, arg);
    *(Pose *)(*(char **)(self + 0x390) + 0x10) = *(Pose *)(self + 0xa0);
    *(Pose *)(**(char ***)(self + 0x38c) + 0x10) = *(Pose *)(*(char **)(self + 0x390) + 0x10);
}
