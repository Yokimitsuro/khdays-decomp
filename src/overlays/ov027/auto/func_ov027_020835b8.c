/* func_ov027_020835b8 -- Ov027_ObjectAimAt: give a display object a step towards a target: the
 * difference between the target and the object's position (+0x10), clamped to +-1.0 (fx32) per
 * axis (Ov027_ClampStep), becomes the object's step (+0x3c). */
typedef unsigned char  u8;
typedef signed char    s8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Fx32Pair {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
} Fx32Pair;

typedef struct Ov027Object {
    u8   pad_00[0x10];
    Fx32Pair vPos;            /* 0x10 */
    Fx32Pair vScale;          /* 0x18 */
    u8   pad_20[4];
    u8   nDepth;              /* 0x24 */
    u8   pad_25[5];
    u8   nAlpha;              /* 0x2a: bits 0-4 */
    u8   pad_2b[5];
    u16  wFlags;              /* 0x30: bit 1 = steer toward the target */
    u8   pad_32[2];
    int  nPhase;              /* 0x34: the float orbit phase */
    int  nSlot;               /* 0x38: the placement slot */
    Fx32Pair vStep;           /* 0x3c */
    u8   pad_44[4];
} Ov027Object;                /* 0x48: an ov002 display object */

static inline void Ov027_ClampStep(Fx32Pair *pStep)
{
    if (pStep->x > 0x1000) {
        pStep->x = 0x1000;
    }
    if (pStep->x < -0x1000) {
        pStep->x = -0x1000;
    }
    if (pStep->y > 0x1000) {
        pStep->y = 0x1000;
    }
    if (pStep->y < -0x1000) {
        pStep->y = -0x1000;
    }
}

void func_ov027_020835b8(Ov027Object *pObject, const Fx32Pair *pTarget)
{
    Fx32Pair vFrom;
    Fx32Pair vDelta;

    vFrom = pObject->vPos;
    vDelta.x = pTarget->x - vFrom.x;
    vDelta.y = pTarget->y - vFrom.y;
    Ov027_ClampStep(&vDelta);
    pObject->vStep = vDelta;
}
