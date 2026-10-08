/* Moves the two trail nodes along one joint (offsets 0x800/0x1000) and a third node to another
 * joint. NNS_G3dGetResultMtx fills one 4x3 matrix, whose last row is the joint's position. */

#include "game/engine.h"
#include "nitro/fx.h"

extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern int NNS_G3dGetResultMtx(const void *pRenderObj, MtxFx43 *pos, MtxFx33 *nrm, unsigned int nodeID);
extern void Srt_SetTranslation(void *transform, const VecFx32 *translation);

struct A {
    char pad88[0x88];
    char *p88;
};

struct B {
    char pad[0x3b4];
    int f3b4;
    int f3b8;
};

void Ov249_SyncEffectNodesToJoints(struct A *a0, struct B *sl) {
    MtxFx43 mtx;
    VecFx32 work;
    int i;

    if (NNS_G3dGetResultMtx(a0->p88 + 0x20, &mtx, 0, sl->f3b4) != 0) {
        char *p;
        Srt_SetTranslation((char *)sl + 0x3e0, (const VecFx32 *)&mtx._30);

        p = (char *)sl + 0xc + 0x400;
        for (i = 0; i < 2; i++) {
            work.x = 0;
            work.y = 0;
            work.z = (i == 0) ? 0x800 : 0x1000;
            Vec3TransformViaTempMtx(&work, (char *)sl + 0xa0, &work);
            VEC_Add(&work, (const VecFx32 *)&mtx._30, &work);
            Srt_SetTranslation(p, &work);
            p += 0x2c;
        }
    }

    if (NNS_G3dGetResultMtx(a0->p88 + 0x20, &mtx, 0, sl->f3b8) == 0)
        return;

    Srt_SetTranslation((char *)sl + 0x64 + 0x400, (const VecFx32 *)&mtx._30);
}
