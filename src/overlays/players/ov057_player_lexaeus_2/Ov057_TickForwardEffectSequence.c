/* Forward-effect sequence for ov057: while the actor is still in stage 0x30 and
 * the gauge has passed 0x1b000, it retunes channel 0xc8, re-arms the sequence
 * block, and places the effect a fixed offset in front of the actor -- the
 * offset is rotated by the actor's own heading through the shared sin/cos
 * table and added to the anchor at +0x48c. The heading is stored back on the
 * record, the visible bit is raised and the state advances to 2, where the
 * emitter runs until it reports done. */

#include "nitro/types.h"
#include "nitro/fx_types.h"

struct Mtx33 { int m[9]; };

extern void Ov022_PlayEntityVoice(int pActor, int nSeqArc, int nSeq);
extern void Ov057_ResetSequenceState(int pActor, void *block);
extern void MTX_RotY33_(struct Mtx33 *m, int sin, int cos);
extern void MTX_MultVec33(const VecFx32 *v, const struct Mtx33 *m, VecFx32 *dst);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern unsigned short Sequence_UpdateTracks(void *p, int a);

extern int data_ov057_020b74a0;
extern short data_0203d210[];

void Ov057_TickForwardEffectSequence(int pActor, int *pEffect, int delta) {
    VecFx32 effectPosition;
    VecFx32 effectOffset;
    struct Mtx33 rotation;
    char *pSceneBlock = (char *)(*(int *)&data_ov057_020b74a0 + 0x2c + 0x2c00);
    u16 heading;
    int sinCosIndex;

    if (*pEffect == 1 && *(int *)(pActor + 0x6bc) != 0x30) {
        *pEffect = 0;
    }
    switch (*pEffect) {
    case 1:
        if (*(int *)(pActor + 0x7b0) < 0x1b000) {
            return;
        }
        Ov022_PlayEntityVoice(pActor, 0xc8, 1);
        Ov057_ResetSequenceState(pActor, pSceneBlock + 0x118);

        effectOffset.x = 0x148;
        effectOffset.y = 0;
        effectOffset.z = 0x1800;
        effectPosition = *(VecFx32 *)(pActor + 0x48c);

        heading = *(u16 *)(*(char **)(pActor + 0x20) + 0x80);
        heading = (u16)(heading - 0x8000);
        heading = (u16)(heading + 0x8000);
        sinCosIndex = heading >> 4;
        MTX_RotY33_(&rotation, data_0203d210[sinCosIndex * 2], data_0203d210[sinCosIndex * 2 + 1]);
        MTX_MultVec33(&effectOffset, &rotation, &effectOffset);
        VEC_Add(&effectPosition, &effectOffset, &effectPosition);

        *(u16 *)((char *)pEffect + 0x80) = heading;
        *(u16 *)((char *)pEffect + 4) |= 0x20;
        *(VecFx32 *)((char *)pEffect + 0xa8) = effectPosition;
        *pEffect = 2;
        return;
    case 2:
        if (Sequence_UpdateTracks((void *)((char *)pEffect + 4), delta) != 0) {
            *pEffect = 0;
        }
        return;
    }
}
