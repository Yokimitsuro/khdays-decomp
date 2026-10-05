
#include "nitro/fx_types.h"

extern void MTX_Identity33_(int *m);
extern void NNS_G3dGlbSetBaseTrans(const VecFx32 *target);
extern void Gfx_ApplyBaseTransform(void);
extern void NNS_G3dDraw(unsigned int *param_1);
extern int data_02047428[9];

extern struct {
    char pad0000[0xc4];
    int field_c4;
    int field_c8;
    int field_cc;
} NNS_G3dGlb;

// Reset the global orientation matrix, then for every list entry (stride 0x38,
// count at +0x8c, array at +0x90) with a live marker at offset 0, stamp the
// marker into the global state's 0xc4/0xc8/0xcc slots, draw the entry's model
// (position at +0x2c), and rerun channels for the object at *(this+0x88)+0x20.
void Ov284_RenderMarkers(char *this)
{
    int i;
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
            NNS_G3dDraw((unsigned int *)(*(int *)(this + 0x88) + 0x20));
        }
    }
}
