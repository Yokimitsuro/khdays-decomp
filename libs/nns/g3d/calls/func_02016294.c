typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000

#define offsetof(type, member) ((u32)&(((type *)0)->member))



typedef vu32 REGType32v;
typedef s32 fx32;
typedef union {
        struct {
            fx32 _00, _01, _02, _03;
            fx32 _10, _11, _12, _13;
            fx32 _20, _21, _22, _23;
            fx32 _30, _31, _32, _33;
        };
        fx32 m[4][4];
        fx32 a[16];
    } MtxFx44;
typedef union {
        struct {
            fx32 _00, _01, _02;
            fx32 _10, _11, _12;
            fx32 _20, _21, _22;
            fx32 _30, _31, _32;
        };
        fx32 m[4][3];
        fx32 a[12];
    } MtxFx43;
typedef union {
        struct {
            fx32 _00, _01, _02;
            fx32 _10, _11, _12;
            fx32 _20, _21, _22;
        };
        fx32 m[3][3];
        fx32 a[9];
    } MtxFx33;
typedef enum {
    GX_MTXMODE_PROJECTION      = 0,
    GX_MTXMODE_POSITION        = 1,
    GX_MTXMODE_POSITION_VECTOR = 2,
    GX_MTXMODE_TEXTURE         = 3
} GXMtxMode;
int G3X_GetClipMtx(MtxFx44 * m);
int G3X_GetVectorMtx(MtxFx33 * m);
extern void G3_MtxMode(GXMtxMode mode);
extern void G3_PushMtx(void);
extern void G3_PopMtx(int num);
extern void G3_Identity(void);
static inline void G3_MtxMode (GXMtxMode mode)
{
    (*( REGType32v *) (0x04000000 + 0x440)) = ((u32) ((mode) << 0)) ;
}
static inline void G3_PushMtx ()
{
    (*( REGType32v *) (0x04000000 + 0x444)) = 0;
}
static inline void G3_PopMtx (int num)
{
    (*( REGType32v *) (0x04000000 + 0x448)) = ((u32) (num)) ;
}
static inline void G3_Identity ()
{
    (*( REGType32v *) (0x04000000 + 0x454)) = 0;
}
extern void MTX_Copy44To43(const MtxFx44 * pSrc, MtxFx43 * pDst);
void MTX_Copy44To43_(register const MtxFx44 * pSrc, register MtxFx43 * pDst);
static inline void MTX_Copy44To43 (const MtxFx44 * pSrc, MtxFx43 * pDst)
{
    MTX_Copy44To43_(pSrc, pDst);
}
void func_01ff80b8(void);

/* func_02016294 -- NitroSystem util.c: NNS_G3dGetCurrentMtx. */
void func_02016294 (MtxFx43 * m, MtxFx33 * n)
{
    func_01ff80b8();

    G3_MtxMode(GX_MTXMODE_PROJECTION);
    G3_PushMtx();
    G3_Identity();

    if (m) {
        MtxFx44 tmp;
        while (G3X_GetClipMtx(&tmp))
            ;
        MTX_Copy44To43(&tmp, m);
    }

    if (n) {
        while (G3X_GetVectorMtx(n))
            ;
    }

    G3_PopMtx(1);
    G3_MtxMode(GX_MTXMODE_POSITION_VECTOR);
}
