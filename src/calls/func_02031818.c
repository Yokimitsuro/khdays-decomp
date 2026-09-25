/* func_02031818 = DispObj_MirrorOam -- mirror a sprite's OAM entry about its owner's centre. Affine and hidden entries
 * are left alone; otherwise, with the owner's flip-X flag (bit 4 of +0x78) the X position is
 * reflected about the owner's +0xc fx32 X (less the sprite width, func_02031730) and the H flip
 * toggled on, and likewise for Y with flip-Y (bit 5), the +0x10 Y and the height (func_02031644).
 * The effect is written back through G2_SetOBJEffect with `rsParam`. */
typedef unsigned int u32;
typedef int fx32;

typedef struct GXOamAttr {
    u32 attr01;
    unsigned short attr2;
    unsigned short _3;
} GXOamAttr;

typedef enum {
    GX_OAM_EFFECT_NONE = 0x0000,
    GX_OAM_EFFECT_FLIP_H = 0x10000000,
    GX_OAM_EFFECT_FLIP_V = 0x20000000,
    GX_OAM_EFFECT_FLIP_HV = 0x30000000,
    GX_OAM_EFFECT_AFFINE = 0x0100,
    GX_OAM_EFFECT_NODISPLAY = 0x0200,
    GX_OAM_EFFECT_AFFINE_DOUBLE = 0x0300
} GXOamEffect;

#define GX_OAM_ATTR01_Y_MASK        0x000000ff
#define GX_OAM_ATTR01_RSENABLE_MASK 0x00000300
#define GX_OAM_ATTR01_X_SHIFT       16
#define GX_OAM_ATTR01_X_MASK        0x01ff0000
#define GX_OAM_ATTR01_RS_SHIFT      25
#define GX_OAM_ATTR01_RS_MASK       0x3e000000
#define GX_OAM_ATTR01_FLIP_MASK     0x30000000

static inline void G2_SetOBJPosition(GXOamAttr *oam, int x, int y)
{
    oam->attr01 = ((oam->attr01 & ~(GX_OAM_ATTR01_Y_MASK | GX_OAM_ATTR01_X_MASK)) |
                   (y & GX_OAM_ATTR01_Y_MASK) |
                   ((x & (GX_OAM_ATTR01_X_MASK >> GX_OAM_ATTR01_X_SHIFT)) << GX_OAM_ATTR01_X_SHIFT));
}

static inline void G2_GetOBJPosition(const GXOamAttr *oam, u32 *x, u32 *y)
{
    *x = (oam->attr01 & GX_OAM_ATTR01_X_MASK) >> GX_OAM_ATTR01_X_SHIFT;
    *y = oam->attr01 & GX_OAM_ATTR01_Y_MASK;
}

static inline void G2_SetOBJEffect(GXOamAttr *oam, GXOamEffect effect, int rsParam)
{
    if (GX_OAM_EFFECT_AFFINE != effect && GX_OAM_EFFECT_AFFINE_DOUBLE != effect) {
        oam->attr01 = ((oam->attr01 & ~(GX_OAM_ATTR01_RSENABLE_MASK | GX_OAM_ATTR01_RS_MASK)) | effect);
    } else {
        oam->attr01 = ((oam->attr01 & ~(GX_OAM_ATTR01_RSENABLE_MASK | GX_OAM_ATTR01_RS_MASK)) |
                       effect | (rsParam << GX_OAM_ATTR01_RS_SHIFT));
    }
}

static inline GXOamEffect G2_GetOBJEffect(const GXOamAttr *oam)
{
    GXOamEffect effect;

    effect = (GXOamEffect)(oam->attr01 & GX_OAM_ATTR01_RSENABLE_MASK);
    if (effect == GX_OAM_EFFECT_AFFINE || effect == GX_OAM_EFFECT_AFFINE_DOUBLE) {
        return effect;
    }
    return (GXOamEffect)(effect | (oam->attr01 & GX_OAM_ATTR01_FLIP_MASK));
}

struct DispObjFlags { unsigned int b0 : 1, b1 : 1, b2 : 1, b3 : 1, flipX : 1, flipY : 1; };

typedef struct DispObj {
    char pad00[0xc];
    fx32 x;                             /* +0x0c */
    fx32 y;                             /* +0x10 */
    char pad14[0x78 - 0x14];
    struct DispObjFlags flags;      /* +0x78 */
} DispObj;

extern int func_02031730(GXOamAttr *oam);   /* Oam_GetObjWidth */
extern int func_02031644(GXOamAttr *oam);   /* Oam_GetObjHeight */

void func_02031818(DispObj *owner, GXOamAttr *oam, int rsParam)
{
    GXOamEffect effect = G2_GetOBJEffect(oam);
    /* The centres are declared before x/y and each size is fetched into its own local before the
     * flip bit is set; that is the ROM's register assignment and instruction order. */
    fx32 cx;
    fx32 cy;
    u32 x;
    u32 y;

    if (effect == GX_OAM_EFFECT_AFFINE || effect == GX_OAM_EFFECT_NODISPLAY ||
        effect == GX_OAM_EFFECT_AFFINE_DOUBLE) {
        return;
    }
    G2_GetOBJPosition(oam, &x, &y);
    if (owner->flags.flipX == 1) {
        u32 width;

        cx = owner->x;
        width = func_02031730(oam);
        effect |= GX_OAM_EFFECT_FLIP_H;
        x = (x - (cx >> 12)) * -1 + (cx >> 12) - width;
    }
    if (owner->flags.flipY == 1) {
        u32 height;

        cy = owner->y;
        height = func_02031644(oam);
        effect |= GX_OAM_EFFECT_FLIP_V;
        y = (y - (cy >> 12)) * -1 + (cy >> 12) - height;
    }
    G2_SetOBJEffect(oam, effect, rsParam);
    G2_SetOBJPosition(oam, (int)x, (int)y);
}
