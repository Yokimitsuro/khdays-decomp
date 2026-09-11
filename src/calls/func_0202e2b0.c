typedef signed long fx32;

extern int FX_Inv(int x, int unused);
extern const short data_0203d210[];

/* src: the same object func_0202e1cc reads. field_4c/50/54 are a VecFx32-shaped
 * triple; only field_4c takes part in the angle computation here, the other two
 * are copied through unchanged. */
typedef struct Src {
    fx32 pad_00[0x13];
    fx32 field_4c;
    fx32 field_50;
    fx32 field_54;
} Src;

/* self: field_10/field_14 hold the cos/sin pair for the derived heading,
 * field_1c/field_20 mirror src's field_50/field_54. */
typedef struct Self {
    fx32 pad_00[4];
    fx32 field_10;
    fx32 field_14;
    fx32 pad_18;
    fx32 field_1c;
    fx32 field_20;
} Self;

/* Derive a heading from the reciprocal of src->field_4c, scaled by 0xc00 in
 * 12-bit fixed point, and store its cos/sin pair on self. The 0x28be60db9391
 * magic is the shared fixed-point-to-table-index conversion also used by
 * func_ov280_020d06bc and friends. */
void func_0202e2b0(Self *self, Src *src)
{
    int angle = (int)(((unsigned)(((long long)(int)(unsigned)(int)((((long long)
                 FX_Inv(src->field_4c, 0x2000) * 0xc00 + 0x800) >> 12))
                 * 0x28be60db9391LL + 0x80000000000LL) >> 0x20) << 4) >> 0x10) >> 4;

    self->field_1c = src->field_50;
    self->field_20 = src->field_54;
    self->field_10 = data_0203d210[angle * 2];
    self->field_14 = data_0203d210[angle * 2 + 1];
}
