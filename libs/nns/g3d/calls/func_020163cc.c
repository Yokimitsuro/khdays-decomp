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
typedef enum {
    GX_FIFOINTR_COND_DISABLE      = 0,
    GX_FIFOINTR_COND_UNDERHALF    = 1,
    GX_FIFOINTR_COND_EMPTY        = 2
} GXFifoIntrCond;
void G3X_Init(void);
extern void G3X_SetFifoIntrCond(GXFifoIntrCond cond);
static inline void G3X_SetFifoIntrCond (GXFifoIntrCond cond)
{
    (*( REGType32v *) (0x04000000 + 0x600)) = (((*( REGType32v *) (0x04000000 + 0x600)) & ~0xc0000000 ) |
                      (cond << 30 ));
}
void func_02015630(void);

/* func_020163cc -- NitroSystem util.c: NNS_G3dInit. */
void func_020163cc (void)
{
    G3X_Init();

    func_02015630();

    G3X_SetFifoIntrCond(GX_FIFOINTR_COND_EMPTY);
}
