/* Bone callback of the ov291 enemy, run while the model's joints are drawn. When the joint id (the
 * +0xae byte when bit 4 of +8 is set, else 0xffff) is the actor's +0x39c head joint: takes the
 * joint's 4x3/3x3 pair, lifts the subscriber's +0x44 height by 0x200 and uses it as the Y of the
 * joint position, tilts the joint rotation by the overlay's quaternion and keeps only its yaw
 * (heading of the rotated world Z), places the +0x398 item there with that yaw, re-centres the
 * +0x38c item at (x, actor +0xb4, z), copies its placement to the first +0x390 item, and clears
 * the joint's +0x24 word and +0x92 byte. */

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
extern const Quat data_ov291_020cd604;
extern void Quat_Multiply(Quat *out, Quat *a, const Quat *b);
extern void Srt_SetTranslationXYZ(void *transform, int x, int y, int z);
typedef struct { int w[11]; } SrtTransform;

void Ov291_HeadBoneCallback(char *joint)
{
    char *actor = *(char **)(*(char **)(joint + 4) + 0x2c);
    MtxFx43 m43;
    MtxFx33 m33;
    Quat rot;
    VecFx32 at;
    VecFx32 fwd;
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
    NNS_G3dGetCurrentMtx(&m43, &m33);
    Quat_FromMtx33(&rot, &m33);
    at = m43.t;
    *(int *)(*(char **)(actor + 0x9c) + 0x44) += 0x200;
    at.y = *(int *)(*(char **)(actor + 0x9c) + 0x44);
    Quat_Multiply(&rot, &rot, &tilt);
    Vec3TransformViaTempMtx(&fwd, &rot, &data_02042258);
    QuatFromAxisAngle(&rot, &data_02042264, FX_Atan2(fwd.x, fwd.z));
    SrtTransform_SetIdentity(*(char **)(actor + 0x398) + 0x30);
    Srt_SetRotationQuat(*(char **)(actor + 0x398) + 0x30, &rot);
    Srt_SetTranslation(*(char **)(actor + 0x398) + 0x30, &at);
    SrtTransform_SetIdentity(*(char **)(actor + 0x38c) + 0x10);
    Srt_SetTranslationXYZ(*(char **)(actor + 0x38c) + 0x10, at.x, *(int *)(actor + 0xb4), at.z);
    *(SrtTransform *)(*(char **)(*(char **)(actor + 0x390)) + 0x10) = *(SrtTransform *)(*(char **)(actor + 0x38c) + 0x10);
    *(int *)(joint + 0x24) = 0;
    *(unsigned char *)(joint + 0x92) = 0;
}
