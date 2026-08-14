/* Syncs the subitem pose to a model joint (Ghidra: ov264_syncSubitemPoseToJoint).
 *
 * Reads the world transform of joint id self+0x438 out of the model at
 * scene+0x88+0x20 with the geometry engine helper at 02016320, which reads back
 * the 3x3 vector matrix and then its translation row, so the single out buffer
 * is a 48 byte MtxFx43. When the read succeeds it takes that translation,
 * subtracts 0x1400 of the current camera vector at +0x7c, stores the result as
 * the translation of the SRT at self+0x3f4 with uniform scale 0x1000, and
 * publishes the raw joint translation to the two list nodes at self+0x3ac and
 * self+0x3b0.
 *
 * The 44 byte pose block copy from self+0xa0 to self+0x3c8 runs unconditionally,
 * which is why it sits outside the guard.
 */
typedef struct { int x, y, z; } VecFx32;
typedef struct { int m[9]; } MtxFx33;

typedef struct {
    MtxFx33 rotation;
    VecFx32 translation;
} MtxFx43;

typedef struct { int w[11]; } PoseBlock;

extern int func_02016320(void *model, MtxFx43 *out, void *opt, unsigned int jointId);
extern void func_0203c960(void *srt);
extern void *OS_IsThreadAvailable_0x020c9848(void);
extern void func_01ffa724(int scale, const VecFx32 *src, VecFx32 *dst);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern void func_0203ca30(void *srt, const VecFx32 *translation);
extern void func_0203ca9c(void *srt, int scale);

void func_ov214_020cbfc8(int *scene, char *self)
{
    MtxFx43 jointXfm;
    VecFx32 position;
    VecFx32 cameraOffset;

    if (func_02016320((char *)scene[0x22] + 0x20, &jointXfm, 0,
                      *(unsigned int *)(self + 0x438)) != 0) {
        position = jointXfm.translation;
        func_0203c960(self + 0x3f4);
        func_01ffa724(-0x1400,
                      (const VecFx32 *)(*(char **)OS_IsThreadAvailable_0x020c9848() + 0x7c),
                      &cameraOffset);
        VEC_Add(&position, &cameraOffset, &position);
        func_0203ca30(self + 0x3f4, &position);
        func_0203ca9c(self + 0x3f4, 0x1000);
        func_0203ca30(*(char **)*(char **)(self + 0x3ac) + 0x10, &jointXfm.translation);
        func_0203ca30(*(char **)(self + 0x3b0) + 0x10, &jointXfm.translation);
    }
    *(PoseBlock *)(self + 0x3c8) = *(PoseBlock *)(self + 0xa0);
}
