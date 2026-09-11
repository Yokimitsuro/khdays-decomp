typedef struct { int x, y, z; } VecFx32;

extern void VEC_Subtract(VecFx32 *a, VecFx32 *b, VecFx32 *out);
extern int func_01ff8d18(VecFx32 *out, VecFx32 *in);
extern int func_020050b4(int x, int z);
/* The symbol named FX_Inv at 0x01ff8a04 forwards r0 AND r1 to FX_DivAsync: it is
   the SDK's FX_Div(numer, denom). Declared with both parameters for that reason. */
extern int FX_Inv(int numer, int denom);

#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

struct State {
    int owner;
    VecFx32 *pos;
    int field_08;
    char pad0c[0x1c];
    int angle28;
    int atten2c;
};

void func_ov299_020d410c(struct State *self, VecFx32 *target, int value) {
    VecFx32 delta;
    int mag;
    int clamped;

    self->field_08 = value;
    VEC_Subtract(target, self->pos, &delta);
    mag = func_01ff8d18(&delta, &delta);
    self->angle28 = func_020050b4(delta.x, delta.z);
    clamped = FX_Inv(mag, 0xc8000);
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
