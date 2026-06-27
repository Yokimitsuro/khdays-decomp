typedef int fx32;
typedef short s16;
typedef unsigned short u16;

extern void FX_DivAsync(fx32 num, fx32 denom);
extern fx32 FX_GetDivResult(void);

typedef struct {
    char pad0[0x20];
    s16 unk20;
    s16 unk22;
    char pad24[0x2c - 0x24];
    u16 unk2c;
    u16 unk2e;
} S_in;

typedef struct {
    fx32 unk00;
    fx32 unk04;
    char pad08[0x10 - 0x08];
    fx32 unk10;
    fx32 unk14;
    char pad18[0x30 - 0x18];
    fx32 unk30;
    fx32 unk34;
} S_out;

void func_02019594(S_out *out, S_in *in)
{
    fx32 a = (fx32)in->unk2c << 12;
    fx32 b = (fx32)in->unk2e << 12;

    FX_DivAsync(b, a);
    out->unk00 = in->unk22;
    out->unk14 = in->unk22;
    out->unk04 = (-(fx32)in->unk20 * FX_GetDivResult()) >> 12;

    FX_DivAsync(a, b);
    out->unk30 = ((fx32)in->unk2c * ((fx32)(-((fx32)in->unk20 + (fx32)in->unk22)) + 0x1000)) << 3;
    out->unk34 = ((fx32)in->unk2e * (((fx32)in->unk20 - (fx32)in->unk22) + 0x1000)) << 3;
    out->unk10 = ((fx32)in->unk20 * FX_GetDivResult()) >> 12;
}
