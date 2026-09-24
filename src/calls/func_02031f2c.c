/* func_02031f2c -- finish a display object's OAM entries, MAIN. For each of the `numOams` entries
 * built from its cell: rebases the character name on the object's resource (+0x58 of the entry
 * func_02031c30 finds for +0x74), keeps window/bitmap modes but otherwise picks translucent when
 * bit 3 of +0x78 is set, applies the palette override +0x6c (-1 keeps the cell's), mirrors the
 * entry for the object's flip flags (func_02031818), sets the priority +0x70 and hands the entry
 * on with the affine index (func_02031a74). */
typedef unsigned short u16;
typedef unsigned int u32;
typedef int fx32;

typedef struct {
    union {
        u32 attr01;
        struct {
            u16 attr0;
            u16 attr1;
        };
    };
    union {
        struct {
            u16 attr2;
            u16 _3;
        };
        u32 attr23;
        struct {
            u32 charNo : 10;
            u32 priority : 2;
            u32 cParam : 4;
            u32 _2 : 16;
        };
    };
} GXOamAttr;

typedef enum {
    GX_OAM_MODE_NORMAL = 0,
    GX_OAM_MODE_XLU = 1,
    GX_OAM_MODE_OBJWND = 2,
    GX_OAM_MODE_BITMAPOBJ = 3
} GXOamMode;

#define GX_OAM_ATTR01_MODE_SHIFT   10
#define GX_OAM_ATTR01_MODE_MASK    0x00000c00
#define GX_OAM_ATTR2_NAME_MASK     0x03ff
#define GX_OAM_ATTR2_PRIORITY_SHIFT 10
#define GX_OAM_ATTR2_PRIORITY_MASK 0x0c00
#define GX_OAM_ATTR2_CPARAM_SHIFT  12
#define GX_OAM_ATTR2_CPARAM_MASK   0xf000

static inline void G2_SetOBJPriority(GXOamAttr *oam, int priority)
{
    oam->attr2 = (u16)((oam->attr2 & ~GX_OAM_ATTR2_PRIORITY_MASK) | (priority << GX_OAM_ATTR2_PRIORITY_SHIFT));
}

static inline void G2_SetOBJMode(GXOamAttr *oam, GXOamMode mode, int cParam)
{
    oam->attr01 = ((oam->attr01 & ~GX_OAM_ATTR01_MODE_MASK) | (mode << GX_OAM_ATTR01_MODE_SHIFT));
    oam->attr2 = (u16)((oam->attr2 & ~GX_OAM_ATTR2_CPARAM_MASK) | (cParam << GX_OAM_ATTR2_CPARAM_SHIFT));
}

static inline GXOamMode G2_GetOBJMode(const GXOamAttr *oam)
{
    return (GXOamMode)((oam->attr01 & GX_OAM_ATTR01_MODE_MASK) >> GX_OAM_ATTR01_MODE_SHIFT);
}

static inline void G2_SetOBJCharName(GXOamAttr *oam, int name)
{
    oam->attr2 = (u16)((oam->attr2 & ~GX_OAM_ATTR2_NAME_MASK) | name);
}

static inline int G2_GetOBJCharName(const GXOamAttr *oam)
{
    return oam->attr2 & GX_OAM_ATTR2_NAME_MASK;
}

struct DispObjFlags { unsigned int visible : 1, b1 : 1, b2 : 1, translucent : 1; };

typedef struct DispObj {
    char pad00[0x6c];
    int palette;                        /* +0x6c, -1 = keep the cell's */
    int priority;                       /* +0x70 */
    int resId;                          /* +0x74 */
    struct DispObjFlags flags;          /* +0x78 */
} DispObj;

typedef struct DispRes {
    char pad00[0x58];
    int charBase;                       /* +0x58 */
} DispRes;

extern DispRes *func_02031c30(void *base, int resId);
extern void func_02031818(DispObj *obj, GXOamAttr *oam, int rsParam);
extern void func_02031a74(void *base, GXOamAttr *oam, int affineIndex);

void func_02031f2c(void *base, DispObj *obj, GXOamAttr *pOams, u16 numOams, int affineIndex)
{
    int charBase = func_02031c30(base, obj->resId)->charBase;
    GXOamMode xluMode = obj->flags.translucent ? GX_OAM_MODE_XLU : GX_OAM_MODE_NORMAL;
    int i;

    for (i = 0; i < numOams; i++, pOams++) {
        GXOamMode mode;

        G2_SetOBJCharName(pOams, G2_GetOBJCharName(pOams) + charBase);
        switch (G2_GetOBJMode(pOams)) {
        case GX_OAM_MODE_OBJWND:
            mode = GX_OAM_MODE_OBJWND;
            break;
        case GX_OAM_MODE_BITMAPOBJ:
            mode = GX_OAM_MODE_BITMAPOBJ;
            break;
        default:
            mode = xluMode;
            break;
        }
        if (obj->palette != -1) {
            G2_SetOBJMode(pOams, mode, obj->palette);
        } else {
            G2_SetOBJMode(pOams, mode, pOams->cParam);
        }
        func_02031818(obj, pOams, affineIndex);
        G2_SetOBJPriority(pOams, obj->priority);
        func_02031a74(base, pOams, affineIndex);
    }
}
