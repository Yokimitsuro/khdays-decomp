/* func_0203cac0 -- concatenate two SRT transforms, MAIN: *out = parent * child. A transform is a
 * quaternion (+0x00), a translation (+0x10), a scale (+0x1c) and flags (+0x28: bit 0 identity,
 * bit 1 uniform scale, only scale.x used). An identity side just copies the other. A uniformly
 * scaled parent composes directly: rotations multiply (func_0202ef54), the child's translation is
 * rotated by the parent (func_0202f384), scaled and offset, and the scales multiply. Otherwise
 * both sides become scaled rotation matrices, the product sets the rotation/scale (func_0203c9ec)
 * and the child's translation goes through the parent matrix. */
typedef int fx32;

typedef struct { fx32 x, y, z; } VecFx32;
typedef struct { fx32 w, x, y, z; } Quat;
typedef struct { fx32 m[9]; } MtxFx33;

typedef struct SrtFlags {
    unsigned char identity : 1;
    unsigned char uniformScale : 1;
} SrtFlags;

typedef struct Srt {
    Quat rot;                           /* +0x00 */
    VecFx32 trans;                      /* +0x10 */
    VecFx32 scale;                      /* +0x1c */
    SrtFlags flags;                     /* +0x28 */
} Srt;

extern void func_0202ef54(Srt *out, const Srt *a, const Srt *b);          /* Quat_Mul */
extern void func_0202f384(VecFx32 *out, const Srt *rot, const VecFx32 *in);  /* Quat_RotateVec */
extern void func_01ffa724(fx32 scale, const VecFx32 *src, VecFx32 *dst);  /* VEC_Scale */
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void func_0203ca30(Srt *srt, const VecFx32 *trans);                /* Srt_SetTrans */
extern void func_0203ca9c(Srt *srt, fx32 scale);                          /* Srt_SetUniformScale */
extern void func_0203ca74(Srt *srt, const VecFx32 *scale);                /* Srt_SetScale */
extern void func_0202ec2c(MtxFx33 *mtx, const Srt *rot);                  /* Quat_ToMtx33 */
extern void func_0203cf0c(MtxFx33 *dst, const MtxFx33 *mtx, const VecFx32 *scale);
extern void MTX_Concat33(const MtxFx33 *a, const MtxFx33 *b, MtxFx33 *ab);
extern void func_0203c9ec(Srt *srt, const MtxFx33 *mtx);                  /* Srt_SetFromMtx33 */
extern void MTX_MultVec33(const VecFx32 *vec, const MtxFx33 *m, VecFx32 *dst);

#define FX_MUL(a, b) ((fx32)(((long long)(a) * (b) + 0x800) >> 12))

void func_0203cac0(Srt *out, const Srt *parent, const Srt *child)
{
    VecFx32 v;
    MtxFx33 parentMtx;
    MtxFx33 childMtx;
    MtxFx33 prod;

    if (parent->flags.identity) {
        *out = *child;
        return;
    }
    if (child->flags.identity) {
        *out = *parent;
        return;
    }
    if (parent->flags.uniformScale) {
        func_0202ef54(out, parent, child);
        func_0202f384(&v, parent, &child->trans);
        func_01ffa724(parent->scale.x, &v, &v);
        VEC_Add(&v, &parent->trans, &v);
        func_0203ca30(out, &v);
        if (child->flags.uniformScale) {
            func_0203ca9c(out, FX_MUL(parent->scale.x, child->scale.x));
        } else {
            func_01ffa724(parent->scale.x, &child->scale, &v);
            func_0203ca74(out, &v);
        }
        return;
    }
    func_0202ec2c(&parentMtx, parent);
    func_0203cf0c(&parentMtx, &parentMtx, &parent->scale);
    func_0202ec2c(&childMtx, child);
    func_0203cf0c(&childMtx, &childMtx, &child->scale);
    MTX_Concat33(&parentMtx, &childMtx, &prod);
    func_0203c9ec(out, &prod);
    MTX_MultVec33(&child->trans, &parentMtx, &v);
    VEC_Add(&v, &parent->trans, &v);
    func_0203ca30(out, &v);
}
