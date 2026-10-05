/* Ov253_CarriedItemUpdate -- carried item update: after the base update (0203bc78) the +0x84
 * owner's +0x440 item takes this transform (+0x30); when the +0x88 model's +0x43c joint can be
 * read back (02016320) a fresh transform is built at the joint's translation, rotated by its
 * matrix, composed with the data_ov253_020d4834 rotation and normalised, and copied into the
 * +0x440 item and from there into the +0x444 slot's item. */

#include "nitro/fx_types.h"

typedef struct { int m[9]; } MtxFx33;
typedef struct { MtxFx33 rotation; VecFx32 translation; } MtxFx43;
typedef struct { int w[11]; } Pose44;
struct vec4 { int a, b, c, d; };
struct Ov253Item { char pad[0x10]; Pose44 pose; };
struct Ov253Actor { char pad[0x30]; Pose44 pose; };

extern void Obj_RenderModel(int self, int arg);
extern int NNS_G3dGetResultMtx(void *model, MtxFx43 *out, MtxFx33 *rot, unsigned int jointId);
extern void SrtTransform_SetIdentity(Pose44 *srt);
extern void Srt_SetTranslation(Pose44 *srt, const VecFx32 *translation);
extern void Node_SetRotationFromMtx(Pose44 *srt, const MtxFx33 *rot);
extern void Quat_Multiply(Pose44 *out, const Pose44 *a, const struct vec4 *b);
extern void Vec4_Normalize(Pose44 *out, const Pose44 *a);
extern const struct vec4 data_ov253_020d4834;

void Ov253_CarriedItemUpdate(int self, int arg) {
    int owner = *(int *)(self + 0x84);
    MtxFx43 joint;
    MtxFx33 rot;
    struct vec4 turn = data_ov253_020d4834;
    Pose44 srt;

    Obj_RenderModel(self, arg);
    ((struct Ov253Item *)*(int *)(owner + 0x440))->pose = ((struct Ov253Actor *)self)->pose;
    if (NNS_G3dGetResultMtx((void *)(*(int *)(self + 0x88) + 0x20), &joint, &rot, *(unsigned int *)(owner + 0x43c)) == 0) {
        return;
    }
    SrtTransform_SetIdentity(&srt);
    Srt_SetTranslation(&srt, &joint.translation);
    Node_SetRotationFromMtx(&srt, &rot);
    Quat_Multiply(&srt, &srt, &turn);
    Vec4_Normalize(&srt, &srt);
    ((struct Ov253Item *)*(int *)(owner + 0x440))->pose = srt;
    ((struct Ov253Item *)*(int *)(*(int *)(owner + 0x444)))->pose = ((struct Ov253Item *)*(int *)(owner + 0x440))->pose;
}
