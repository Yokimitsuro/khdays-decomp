#include "nitro/fx_types.h"
#include "game/engine.h"

typedef struct { char pad0[0x24]; VecFx32 pos; } Probe;

extern void Obj_RenderModel(int a, int b);
extern int NNS_G3dGetResultMtx(int a, Probe *out, int b, int c);
extern int VEC_Subtract(void *a, void *b, void *out);
extern int VEC_Mag(void *v);
extern VecFx32 data_02041dc8;

/* Re-probe the world and refresh the cached aim point (and its byte-identical twins). Sibling
 * of Ov212_ProbeAndCacheHit, which probes the same way; this one also keeps the delta
 * from the previous hit and stores its length at owner+0x578. Once the actor is no
 * longer held (obj+0xad), stop: cancel the pending animation, and clear the cached
 * point, its distance and the two stance bytes. */
void Ov267_RefreshAimPoint(int obj, int param_2) {
    Probe probe;
    VecFx32 hit;
    VecFx32 delta;
    int owner = *(int *)(obj + 0x84);
    short v;

    Obj_RenderModel(obj, param_2);
    if (NNS_G3dGetResultMtx(*(int *)(obj + 0x88) + 0x20, &probe, 0, *(int *)(owner + 0x588)) != 0) {
        hit = probe.pos;
        VEC_Subtract(&hit, (void *)(owner + 0x4e4), &delta);
        *(VecFx32 *)(owner + 0x4e4) = hit;
        *(int *)(owner + 0x578) = VEC_Mag(&delta);
    }
    if (*(unsigned char *)(obj + 0xad) != 0) {
        return;
    }
    v = *(short *)(*(int *)(obj + 0x88) + 2);
    if (v >= 0) {
        SetSubitemState((void *)obj, 0, v, 0);
    }
    *(int *)(owner + 0x578) = 0;
    *(VecFx32 *)(owner + 0x4e4) = data_02041dc8;
    *(int *)(owner + 0x5dc) = 0;
    *(char *)(owner + 0x5e0) = 0;
    *(char *)(owner + 0x5e1) = 0;
}
