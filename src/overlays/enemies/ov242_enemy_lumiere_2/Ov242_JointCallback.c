/* Bone callback of the ov241 enemy (x3: ov241/242/243), run while the model's joints are
 * drawn: the joint id (the +0xae byte when bit 4 of +8 is set, else 0xffff) is compared with
 * the actor's three ids at +0x3ac/+0x3ae/+0x3b0. The first id takes the current 4x3/3x3 pair,
 * places the +0x38c item at the joint, extracts the joint's forward heading (world Z through
 * the joint's rotation) into +0x3bc, raises the subscriber's +0x44 by 0x400 and places the
 * +0x3a0 item with a pure Y rotation of that heading at (actor +0xb0, subscriber +0x44, actor
 * +0xb8). The other two ids only place the +0x390 / +0x394 items at the joint. */

#include "nitro/fx_types.h"

typedef struct { int m[9]; } MtxFx33;
typedef struct { int m[9]; VecFx32 t; } MtxFx43;
typedef struct { int a, b, c, d; } Quat;

extern void NNS_G3dGetCurrentMtx(MtxFx43 *m43, MtxFx33 *m33);
extern void Quat_FromMtx33(Quat *out, MtxFx33 *m33);
extern void SrtTransform_SetIdentity(void *transform);
extern void Srt_SetTranslation(void *transform, const VecFx32 *translation);
extern void Srt_SetRotationQuat(void *transform, Quat *rotation);
extern void Vec3TransformViaTempMtx(VecFx32 *out, Quat *rotation, const VecFx32 *in);
extern fx16 FX_Atan2(int x, int z);
extern void QuatFromAxisAngle(Quat *out, const VecFx32 *axis, int angle);
extern const VecFx32 data_02042258;
extern const VecFx32 data_02042264;

void Ov242_JointCallback(int joint)
{
    int actor = *(int *)(*(int *)(joint + 4) + 0x2c);
    MtxFx43 m43;
    MtxFx33 m33;
    Quat rot;
    VecFx32 at;
    VecFx32 fwd;
    int sel;
    unsigned short id;

    if ((*(int *)(joint + 8) & 0x10) != 0) {
        sel = *(unsigned char *)(joint + 0xae);
    } else {
        sel = -1;
    }
    id = sel;
    if (id == *(unsigned short *)(actor + 0x3ac)) {
        NNS_G3dGetCurrentMtx(&m43, &m33);
        Quat_FromMtx33(&rot, &m33);
        at = m43.t;
        *(int *)(*(int *)(actor + 0x9c) + 0x44) += 0x400;
        at.y = *(int *)(*(int *)(actor + 0x9c) + 0x44);
        SrtTransform_SetIdentity((void *)(*(int *)(actor + 0x38c) + 0x30));
        Srt_SetTranslation((void *)(*(int *)(actor + 0x38c) + 0x30), &m43.t);
        Vec3TransformViaTempMtx(&fwd, &rot, &data_02042258);
        *(int *)(actor + 0x3bc) = FX_Atan2(fwd.x, fwd.z);
        QuatFromAxisAngle(&rot, &data_02042264, *(int *)(actor + 0x3bc));
        at.x = *(int *)(actor + 0xb0);
        at.z = *(int *)(actor + 0xb8);
        SrtTransform_SetIdentity((void *)(*(int *)(actor + 0x3a0) + 0x30));
        Srt_SetRotationQuat((void *)(*(int *)(actor + 0x3a0) + 0x30), &rot);
        Srt_SetTranslation((void *)(*(int *)(actor + 0x3a0) + 0x30), &at);
        return;
    }
    if (id == *(unsigned short *)(actor + 0x3ae)) {
        NNS_G3dGetCurrentMtx(&m43, &m33);
        SrtTransform_SetIdentity((void *)(*(int *)(actor + 0x390) + 0x30));
        Srt_SetTranslation((void *)(*(int *)(actor + 0x390) + 0x30), &m43.t);
        return;
    }
    if (id == *(unsigned short *)(actor + 0x3b0)) {
        NNS_G3dGetCurrentMtx(&m43, &m33);
        SrtTransform_SetIdentity((void *)(*(int *)(actor + 0x394) + 0x30));
        Srt_SetTranslation((void *)(*(int *)(actor + 0x394) + 0x30), &m43.t);
    }
}
