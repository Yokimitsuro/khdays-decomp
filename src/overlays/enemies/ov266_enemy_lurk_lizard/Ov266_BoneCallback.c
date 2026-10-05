/* Bone callback of the ov266 serpent rig: each probed bone (02016320) drives a part.
 * - Bone +0x58c: its point goes to +0x508, the +0xa0 transform is copied to +0x520 and moved to the
 *   point 2.0 behind the +0xa0 transform.
 * - Bone +0x598: the +0xa0 transform is copied to +0x54c at the bone; with bone +0x59c too, the two
 *   +0x4d8 / *+0x4cc parts aim from the first bone to the second (direction +0x64, point 1.5 along
 *   it at +0x58, reach +0x70 = distance - 3.0).
 * - Bones +0x5a0 / +0x5a4 place the +0x10 transforms of the *+0x4d0 / +0x4dc and *+0x4d4 / +0x4e0 parts.
 * While in mode 1 with the +0x3c8 object's bit 1 clear, bone +0x590 roots the sixteen-segment tail:
 * each segment points from the running point towards the +0x4f0 target (height quartered), its yaw
 * limited to 0x86 per link, and once a link folds back past the first one the rest keeps the last
 * orientation; the +0x3cc orientations ease towards it (rate +0x580 growing along the tail), the
 * +0x38c segment transforms take the point, the orientation and the +0x57c length, and the point
 * walks to the next link. The tail end goes to the +0x5d4 object, whose +0xc hook runs when bit 1
 * of its +0x40 flags is set.
 * Codegen: built with `opt_common_subs off` (push/pop scoped) and `obj` declared before the tail
 * locals; with CSE on the tail loop's i/seg registers swap (r8/r6). */

#include "nitro/fx_types.h"
#include "game/engine.h"

typedef struct { int m[9]; } Mtx33;
typedef struct { int m[9]; VecFx32 t; } Mtx43;
typedef struct { int x, y, z, w; } Quat;
typedef struct { int w[11]; } SrtTransform;
typedef struct { int b0 : 1; int b1 : 1; } Flag2;
struct Ov266 {
    char pad000[0x38c];
    int segs[16];           /* +0x38c */
    Quat quats[16];         /* +0x3cc */
};

extern int NNS_G3dGetResultMtx(int a, Mtx43 *out, int b, int bone);
extern void VEC_Add(const void *a, const void *b, void *out);
extern void Srt_SetTranslation(void *srt, const VecFx32 *t);
extern void VEC_Subtract(const void *a, const void *b, void *out);
extern int VEC_Normalize(const VecFx32 *v, void *out);
extern void ScaleVec3Fx12(int scale, const void *v, void *out);
extern int VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern int func_020050b4(int x, int z);
extern int Ov266_WrapSignedDelta6488(int a, int b);
extern void MTX_RotY33_(Mtx33 *m, int sin, int cos);
extern void MTX_MultVec33(const VecFx32 *v, const Mtx33 *m, VecFx32 *out);
extern void Quat_FromTwoVectors(Quat *out, const VecFx32 *from, const VecFx32 *to);
extern void Quat_Slerp(Quat *out, int t, Quat *a, Quat *b);
extern void Srt_SetRotationQuat(void *srt, Quat *q);
extern void Srt_SetScaleXYZ(void *srt, int x, int y, int z);
extern void Obj_LocalToWorld(VecFx32 *out, void *srt, void *in);
extern void Ov107_MoveNodeAndRelayout(int obj, VecFx32 *v);
extern const short data_0203d210[];
extern const VecFx32 data_02042258;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

#pragma push
#pragma opt_common_subs off
void Ov266_BoneCallback(int rig, char *self)
{
    Mtx43 probe;
    VecFx32 first;
    VecFx32 pos;
    Quat quat;
    Quat saved;
    VecFx32 root;
    VecFx32 span;
    VecFx32 dir;
    Mtx33 mtx;
    int k;
    int part;
    int len;
    int obj;
    int i;
    int blocked;
    int weight;
    int ang;
    int prev;
    int seg;

    if (NNS_G3dGetResultMtx(*(int *)(rig + 0x88) + 0x20, &probe, 0, *(int *)(self + 0x58c)) != 0) {
        *(VecFx32 *)(self + 0x508) = probe.t;
        *(SrtTransform *)(self + 0x520) = *(SrtTransform *)(self + 0xa0);
        pos.x = 0;
        pos.y = 0;
        pos.z = -0x2000;
        Vec3TransformViaTempMtx(&pos, self + 0xa0, &pos);
        VEC_Add(&pos, self + 0xb0, &pos);
        Srt_SetTranslation(self + 0x520, &pos);
    }
    if (NNS_G3dGetResultMtx(*(int *)(rig + 0x88) + 0x20, &probe, 0, *(int *)(self + 0x598)) != 0) {
        root = probe.t;
        *(SrtTransform *)(self + 0x54c) = *(SrtTransform *)(self + 0xa0);
        Srt_SetTranslation(self + 0x54c, &root);
        if (NNS_G3dGetResultMtx(*(int *)(rig + 0x88) + 0x20, &probe, 0, *(int *)(self + 0x59c)) != 0) {
            VEC_Subtract(&probe.t, &root, &span);
            for (k = 0; k < 2; k++) {
                part = k == 0 ? *(int *)(self + 0x4d8) : **(int **)(self + 0x4cc);
                len = VEC_Normalize(&span, (void *)(part + 0x64));
                ScaleVec3Fx12(0x1800, (void *)(part + 0x64), (void *)(part + 0x58));
                VEC_Add((void *)(part + 0x58), &root, (void *)(part + 0x58));
                *(int *)(part + 0x70) = len - 0x3000;
            }
        }
    }
    if (NNS_G3dGetResultMtx(*(int *)(rig + 0x88) + 0x20, &probe, 0, *(int *)(self + 0x5a0)) != 0) {
        Srt_SetTranslation((void *)(**(int **)(self + 0x4d0) + 0x10), &probe.t);
        Srt_SetTranslation((void *)(*(int *)(self + 0x4dc) + 0x10), &probe.t);
    }
    if (NNS_G3dGetResultMtx(*(int *)(rig + 0x88) + 0x20, &probe, 0, *(int *)(self + 0x5a4)) != 0) {
        Srt_SetTranslation((void *)(**(int **)(self + 0x4d4) + 0x10), &probe.t);
        Srt_SetTranslation((void *)(*(int *)(self + 0x4e0) + 0x10), &probe.t);
    }
    if (*(int *)(self + 0x50) != 1) {
        return;
    }
    if (((Flag2 *)(*(int *)(self + 0x3c8) + 0x5c))->b1) {
        return;
    }
    if (NNS_G3dGetResultMtx(*(int *)(rig + 0x88) + 0x20, &probe, 0, *(int *)(self + 0x590)) == 0) {
        return;
    }
    blocked = 0;
    pos = probe.t;
    for (i = 0; i < 16; i++) {
        seg = ((struct Ov266 *)self)->segs[i];
        weight = *(int *)(self + 0x580) + i * (*(int *)(self + 0x580) * 5) / 16;
        VEC_Subtract(self + 0x4f0, &pos, &dir);
        dir.y = dir.y * 0x400 / 0x1000;
        VEC_Normalize(&dir, &dir);
        if (i == 0) {
            first = dir;
        }
        if (blocked != 0 || (i != 0 && VEC_DotProduct(&dir, &first) <= 0)) {
            blocked = 1;
            quat = saved;
        } else {
            ang = func_020050b4(dir.x, dir.z);
            if (i != 0) {
                int diff = Ov266_WrapSignedDelta6488(ang, prev);

                if ((diff < 0 ? -diff : diff) >= 0x86) {
                    unsigned int idx;

                    ang = diff > 0x86 ? prev + 0x86 : prev - 0x86;
                    idx = ANG2IDX(ang);
                    dir.x = 0;
                    dir.z = 0x1000;
                    MTX_RotY33_(&mtx, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
                    MTX_MultVec33(&dir, &mtx, &dir);
                }
            }
            prev = ang;
            Quat_FromTwoVectors(&quat, &data_02042258, &dir);
            saved = quat;
        }
        Quat_Slerp(&quat, weight, &((struct Ov266 *)self)->quats[i], &quat);
        ((struct Ov266 *)self)->quats[i] = quat;
        Srt_SetTranslation((void *)(seg + 0x30), &pos);
        Srt_SetRotationQuat((void *)(seg + 0x30), &quat);
        Srt_SetScaleXYZ((void *)(seg + 0x30), 0x1000, 0x1000, *(int *)(self + 0x57c));
        Obj_LocalToWorld(&pos, (void *)(seg + 0x30), self + 0x4fc);
    }
    Ov107_MoveNodeAndRelayout(*(int *)(self + 0x5d4), &pos);
    obj = *(int *)(self + 0x5d4);
    if (((Flag2 *)(obj + 0x40))->b1 && *(void (**)(int, int))(obj + 0xc) != 0) {
        (*(void (**)(int, int))(obj + 0xc))(obj, 0);
    }
}

#pragma pop
