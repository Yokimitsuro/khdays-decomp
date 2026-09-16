/* func_ov023_02083afc -- Ov023_PlaceObject: set up one of the event scene's model objects (the
 * 0x30-byte ov002 objects at the head of the scene).  With a resource name the object is started
 * on it (ov002 02050cd4) and its alpha set to 0x3c; then its two angles come from the degrees
 * given (x 65536 / 360), its depth is its index x 128 and its position the pair given in whole
 * units (x 4096). */
typedef unsigned char  u8;
typedef signed short   s16;

typedef struct Fx32Pair {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
} Fx32Pair;

typedef struct Ov023Object {
    u8   pad_00[0x10];
    Fx32Pair vPos;            /* 0x10 */
    u8   pad_18[8];
    int  nDepth;              /* 0x20 */
    u8   nAlpha;              /* 0x24 */
    u8   pad_25;
    s16  nAngleA;             /* 0x26 */
    s16  nAngleB;             /* 0x28 */
    u8   pad_2a[6];
} Ov023Object;                /* 0x30 */

typedef struct Ov023Scene {
    Ov023Object aObject[6];   /* 0x00 */
} Ov023Scene;

typedef struct Ov023SceneRoot {
    int  nField00;            /* 0x00 */
    Ov023Scene *pScene;       /* 0x04 */
} Ov023SceneRoot;

extern int  func_ov002_02050cd4(Ov023Object *pObject, const char *pszResource); /* start an object on a resource */
/* The quotient is the low half of the helper's long long return; writing `/` emits _s32_div_f,
 * which is not linkable here. */
extern long long func_02020400(int nNumerator, int nDenominator);
extern Ov023SceneRoot data_ov023_0208a784;

void func_ov023_02083afc(const char *pszResource, int nIndex, int nX, int nY, int nAngleA, int nAngleB)
{
    Fx32Pair vPos;

    if (pszResource != 0) {
        func_ov002_02050cd4(&data_ov023_0208a784.pScene->aObject[nIndex], pszResource);
        data_ov023_0208a784.pScene->aObject[nIndex].nAlpha = 0x3c;
    }
    data_ov023_0208a784.pScene->aObject[nIndex].nAngleA = (s16)func_02020400(nAngleA << 16, 360);
    data_ov023_0208a784.pScene->aObject[nIndex].nAngleB = (s16)func_02020400(nAngleB << 16, 360);
    data_ov023_0208a784.pScene->aObject[nIndex].nDepth = nIndex << 7;
    vPos.x = nX << 12;
    vPos.y = nY << 12;
    data_ov023_0208a784.pScene->aObject[nIndex].vPos = vPos;
}
