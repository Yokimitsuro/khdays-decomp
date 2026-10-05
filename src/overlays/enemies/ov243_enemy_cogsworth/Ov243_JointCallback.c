/* Bone callback of the ov243 enemy (the ov241 variant with a single joint): the joint id (the
 * +0xae byte when bit 4 of +8 is set, else 0xffff) must equal the actor's +0x3a0 id; then the
 * current 4x3/3x3 pair is taken, the subscriber's +0x44 is raised by 0x400, the joint's forward
 * heading (the -Z axis through the joint's rotation) goes to +0x3b0, and the +0x394 item is
 * placed with a pure Y rotation of that heading at (actor +0xb0, subscriber +0x44, actor +0xb8). */

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
extern const VecFx32 data_0204227c;
extern const VecFx32 data_02042264;

void Ov243_JointCallback(int joint)
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
    if (id == *(unsigned short *)(actor + 0x3a0)) {
        NNS_G3dGetCurrentMtx(&m43, &m33);
        Quat_FromMtx33(&rot, &m33);
        at = m43.t;
        *(int *)(*(int *)(actor + 0x9c) + 0x44) += 0x400;
        at.y = *(int *)(*(int *)(actor + 0x9c) + 0x44);
        Vec3TransformViaTempMtx(&fwd, &rot, &data_0204227c);
        *(int *)(actor + 0x3b0) = FX_Atan2(fwd.x, fwd.z);
        QuatFromAxisAngle(&rot, &data_02042264, *(int *)(actor + 0x3b0));
        at.x = *(int *)(actor + 0xb0);
        at.z = *(int *)(actor + 0xb8);
        SrtTransform_SetIdentity((void *)(*(int *)(actor + 0x394) + 0x30));
        Srt_SetRotationQuat((void *)(*(int *)(actor + 0x394) + 0x30), &rot);
        Srt_SetTranslation((void *)(*(int *)(actor + 0x394) + 0x30), &at);
    }
}
