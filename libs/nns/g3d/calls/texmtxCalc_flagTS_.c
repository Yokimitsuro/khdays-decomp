/* texmtxCalc_flagTS_ -- NitroSystem maya.c: texmtxCalc_flagTS_ (scale one, no translation): the
 * texture matrix of a rotation alone. The 2x2 rotation (+0x20 sin, +0x22 cos) is corrected for
 * the texture's aspect ratio (height / width and width / height through the divider), and row 3
 * keeps the rotation centred on the texture: ((1 - sin - cos) * width << 3) and
 * ((1 + sin - cos) * height << 3). */

#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void FX_DivAsync(fx32 num, fx32 denom);
extern fx32 FX_GetDivResult(void);

typedef struct {
    char pad0[0x20];
    s16 sinR;       /* +0x20 */
    s16 cosR;       /* +0x22 */
    char pad24[0x2c - 0x24];
    u16 origW;      /* +0x2c: the texture's width */
    u16 origH;      /* +0x2e: the texture's height */
} TexRotAnm;

typedef struct {
    fx32 m00;
    fx32 m01;
    char pad08[0x10 - 0x08];
    fx32 m10;
    fx32 m11;
    char pad18[0x30 - 0x18];
    fx32 m30;
    fx32 m31;
} TexMtxView;

void texmtxCalc_flagTS_(TexMtxView *out, TexRotAnm *in)
{
    fx32 a = (fx32)in->origW << 12;
    fx32 b = (fx32)in->origH << 12;

    FX_DivAsync(b, a);
    out->m00 = in->cosR;
    out->m11 = in->cosR;
    out->m01 = (-(fx32)in->sinR * FX_GetDivResult()) >> 12;

    FX_DivAsync(a, b);
    out->m30 = ((fx32)in->origW * ((fx32)(-((fx32)in->sinR + (fx32)in->cosR)) + 0x1000)) << 3;
    out->m31 = ((fx32)in->origH * (((fx32)in->sinR - (fx32)in->cosR) + 0x1000)) << 3;
    out->m10 = ((fx32)in->sinR * FX_GetDivResult()) >> 12;
}
