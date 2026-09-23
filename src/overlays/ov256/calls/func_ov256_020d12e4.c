/* Update of an ov256 claw: +0x3a4 takes the +0x390 part model's track-0 frame and +0x3a8 its frame at
 * the part's +2 clip; while it animates the frame is clamped to +0x3a4 plus the owner's +0x3ac part's
 * +0x45c boost (x 512). Then the +0x390 part and the base update run and the +0xa0 pose is copied into
 * the +0x38c model and on to the +0x388 shape. */
typedef unsigned char u8;
typedef struct { int w[11]; } Pose;

extern int func_0203bec0(int model, int track);
extern int func_0203be68(int model, int track, int clip);
extern void func_0203be9c(int model, int track, int frame);
extern void func_ov107_020c9ec8(int part, int arg);
extern void func_ov107_020c6980(char *self, int arg);

void func_ov256_020d12e4(char *self, int arg)
{
    *(int *)(self + 0x3a4) = func_0203bec0(*(int *)(*(int *)(self + 0x390) + 0x3c), 0);
    *(int *)(self + 0x3a8) = func_0203be68(*(int *)(*(int *)(self + 0x390) + 0x3c), 0,
                                           *(short *)(*(int *)(self + 0x390) + 2));
    {
        int model = *(int *)(*(int *)(self + 0x390) + 0x3c);

        if (*(u8 *)(model + 0xad) != 0) {
            if (*(int *)(self + 0x3a4) + (*(int *)(*(int *)(self + 0x3ac) + 0x45c) << 9) < *(int *)(self + 0x3a8)) {
                func_0203be9c(model, 0, *(int *)(self + 0x3a4) + (*(int *)(*(int *)(self + 0x3ac) + 0x45c) << 9));
            } else {
                func_0203be9c(model, 0, *(int *)(self + 0x3a8));
            }
        }
    }
    func_ov107_020c9ec8(*(int *)(self + 0x390), arg);
    func_ov107_020c6980(self, arg);
    *(Pose *)(*(char **)(self + 0x38c) + 0x10) = *(Pose *)(self + 0xa0);
    *(Pose *)(**(char ***)(self + 0x388) + 0x10) = *(Pose *)(*(char **)(self + 0x38c) + 0x10);
}
