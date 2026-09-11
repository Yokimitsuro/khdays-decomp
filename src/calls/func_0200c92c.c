typedef unsigned short u16;
typedef int s32;
typedef long long s64;

/* Four packed u16 fields; shared layout for both the raw input record and
 * the (possibly transformed) output record. */
typedef struct {
    unsigned short field_00;
    unsigned short field_02;
    unsigned short field_04;
    unsigned short field_06;
} Rec;

/* Two adjacent u16 fields copied as one unit (forces the ROM's
 * load-both-then-store-both codegen for a halfword pair). */
typedef struct {
    u16 f0;
    u16 f1;
} Pair;

typedef struct {
    char pad_00[0x34];
    u16 field_34;
} Data_02046390;

extern Data_02046390 data_02046390;

/* Two lines of fixed-point (a, b) coefficients, one per axis, used to
 * linearly interpolate a raw value into a clamped screen coordinate:
 * out = (b * ((raw << 2) - a)) >> 22. */
typedef struct {
    s32 aX;
    s32 pad_04;
    s32 bX;
    s32 aY;
    s32 pad_10;
    s32 bY;
} Coef;

extern Coef data_020463ac;

void func_0200c92c(Rec *out, Rec *in) {
    if (data_02046390.field_34 == 0) {
        *(Pair *)&out->field_00 = *(Pair *)&in->field_00;
        *(Pair *)&out->field_04 = *(Pair *)&in->field_04;
        return;
    }

    {
        Coef *coef = &data_020463ac;

        out->field_04 = in->field_04;
        out->field_06 = in->field_06;

        if (in->field_04 == 0) {
            out->field_00 = 0;
            out->field_02 = 0;
            return;
        }

        {
            int x0 = in->field_00 << 2;
            s64 diff0 = (s64)x0 - coef->aX;
            s32 v0 = (s32)((coef->bX * diff0) >> 22);

            out->field_00 = (u16)v0;
            if ((short)out->field_00 < 0) {
                out->field_00 = 0;
            } else if ((short)out->field_00 > 0xff) {
                out->field_00 = 0xff;
            }

            {
                int x1 = in->field_02 << 2;
                s64 diff1 = (s64)x1 - coef->aY;
                s32 v1 = (s32)((coef->bY * diff1) >> 22);

                out->field_02 = (u16)v1;
                if ((short)out->field_02 < 0) {
                    out->field_02 = 0;
                    return;
                }
                if ((short)out->field_02 > 0xbf) {
                    out->field_02 = 0xbf;
                }
            }
        }
    }
}
