/* Ov237_DrawRingMarkEmpty -- draw the ring entries (stride 0x38, count at +0x8c, array at +0x90):
 * resets the global orientation matrix, and for each entry with a live marker stamps it into
 * the global state's 0xc4/0xc8/0xcc slots, draws the model at the entry's +0x2c with polygon
 * id `i mod 63` on the +0x88 object's +0x78 model and reruns its +0x20 channels. When nothing
 * was drawn bit 1 of +0x5c is raised. */

#include "nitro/fx_types.h"

extern void MTX_Identity33_(int *m);
extern void NNS_G3dGlbSetBaseTrans(const VecFx32 *target);
extern void Gfx_ApplyBaseTransform(void);
extern void NNS_G3dMdlSetMdlPolygonIDAll(void *model, int id);
extern void NNS_G3dDraw(unsigned int *param_1);
extern int data_02047428[9];

extern struct {
    char pad0000[0xc4];
    int field_c4;
    int field_c8;
    int field_cc;
} NNS_G3dGlb;

void Ov237_DrawRingMarkEmpty(char *this) {
    int i;
    int drawn = 0;
    MTX_Identity33_(data_02047428);
    for (i = 0; i < *(int *)(this + 0x8c); i++) {
        char *entry = *(char **)(this + 0x90) + i * 0x38;
        int marker = *(int *)entry;
        if (marker != 0) {
            NNS_G3dGlb.field_c4 = marker;
            NNS_G3dGlb.field_c8 = marker;
            NNS_G3dGlb.field_cc = marker;
            NNS_G3dGlbSetBaseTrans((VecFx32 *)(entry + 0x2c));
            Gfx_ApplyBaseTransform();
            NNS_G3dMdlSetMdlPolygonIDAll(*(void **)(*(int *)(this + 0x88) + 0x78), i % 0x3f);
            NNS_G3dDraw((unsigned int *)(*(int *)(this + 0x88) + 0x20));
            drawn++;
        }
    }
    if (drawn == 0) {
        *(int *)(this + 0x5c) |= 2;
    }
}
