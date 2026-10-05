
#include "nitro/fx_types.h"

extern void VEC_Subtract(VecFx32 *a, VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(VecFx32 *out, VecFx32 *in);
extern fx16 FX_Atan2(int x, int z);
/* The symbol named FX_Inv at 0x01ff8a04 forwards r0 AND r1 to FX_DivAsync: it is
   the SDK's FX_Div(numer, denom). Declared with both parameters for that reason. */
extern int FX_Div(int numer, int denom);

#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

struct State {
    int owner;
    VecFx32 *pos;
    int field_08;
    char pad0c[0x1c];
    int angle28;
    int atten2c;
};

void Ov299_AimAtTarget(struct State *self, VecFx32 *target, int value) {
    VecFx32 delta;
    int mag;
    int clamped;

    self->field_08 = value;
    VEC_Subtract(target, self->pos, &delta);
    mag = VEC_Normalize(&delta, &delta);
    self->angle28 = FX_Atan2(delta.x, delta.z);
    clamped = FX_Div(mag, 0xc8000);
    if (clamped > 0x1000) {
        clamped = 0x1000;
    } else if (clamped < 0) {
        clamped = 0;
    }
    self->atten2c = FX_MUL(clamped, 0x2000) + 0x1800;
    {
        unsigned short *hw = (unsigned short *)(self->owner + 0x60);
        unsigned int h = *hw;
        /* hw60.hi |= 1 -- explicit-shift form (bitfield |= adds a redundant mask) */
        *hw = (unsigned short)(h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 1) << 0x18) >> 0x10));
    }
}
