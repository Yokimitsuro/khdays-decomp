/* Ov266_ProbeAndCacheHit -- reset the sub-object, then probe the world and cache the hit position.
 *
 * One of a 3-member shape family; the twins live in ov212/ov267 and are byte-identical modulo
 * relocs (matched here, fanned out with dedupprop).
 *
 * NNS_G3dGetResultMtx fills a 0x30-byte probe record; only the vector at +0x24 of it is kept, and only
 * when the probe reports a hit. It lands in the owner's slot at +0x4fc. The callback pointer at
 * +0x6c is re-armed to Obj_RenderModel either way -- note that is the same function called directly
 * a few lines above, so the pool entry does double duty as a value and as a call target. */

#include "nitro/fx_types.h"

typedef struct {
    char pad0[0x24];
    VecFx32 pos;
} Probe;

extern void SrtTransform_SetIdentity(int a);
extern void Obj_RenderModel(int a, int b);
extern int NNS_G3dGetResultMtx(int a, Probe *out, int b, int c);

void Ov266_ProbeAndCacheHit(int obj) {
    Probe probe;
    int owner;

    owner = *(int *)(obj + 0x84);
    SrtTransform_SetIdentity(obj + 0x30);
    Obj_RenderModel(obj, 1);
    if (NNS_G3dGetResultMtx(*(int *)(obj + 0x88) + 0x20, &probe, 0, *(int *)(owner + 0x594)) != 0) {
        *(VecFx32 *)(owner + 0x4fc) = probe.pos;
    }
    *(void **)(obj + 0x6c) = (void *)Obj_RenderModel;
}
