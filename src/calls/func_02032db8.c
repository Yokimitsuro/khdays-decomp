#pragma thumb on
/* func_02032db8 -- create the sound context (data_0204c234), MAIN. Once only: allocates and clears
 * the 0xb47b8-byte context, starts the sound system (func_02019b68) and carves its sound heaps
 * (NNS_SndHeapCreate): the main 0x5e400-byte heap, the four 0x1c00-byte data banks (each marked
 * free, unreferenced and unmapped), a 0x4b000-byte stream heap and a 0x4000-byte effect heap. Then
 * func_02032844 runs and the playback defaults are set (volumes 0xa000 / 0x32000, levels 0x7f,
 * scale 1.0). Returns TRUE. */
typedef unsigned char u8;
typedef signed char s8;
typedef short s16;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int BOOL;
typedef struct NNSSndHeap *NNSSndHeapHandle;

#define SND_BANK_NUM 4
#define SND_BANK_SIZE 0x1c00

typedef struct SoundCtx {
    char pad000000[0xa0];
    char mainArea[0x5e400];                         /* +0x000a0 */
    char bankArea[SND_BANK_NUM][SND_BANK_SIZE];     /* +0x5e4a0 */
    char streamArea[0x4b000];                       /* +0x654a0 */
    NNSSndHeapHandle mainHeap;                      /* +0xb04a0 */
    NNSSndHeapHandle bankHeap[SND_BANK_NUM];        /* +0xb04a4 */
    NNSSndHeapHandle streamHeap;                    /* +0xb04b4 */
    char effectArea[0x4000];                        /* +0xb04b8 */
    NNSSndHeapHandle effectHeap;                    /* +0xb44b8 */
    char pad0b44bc[0xb44cc - 0xb44bc];
    int fade[3];                                    /* +0xb44cc */
    int scale;                                      /* +0xb44d8 */
    int pan[2];                                     /* +0xb44dc */
    char pad0b44e4[0xb46ec - 0xb44e4];
    int volumeA;                                    /* +0xb46ec */
    int volumeB;                                    /* +0xb46f0 */
    u16 level;                                      /* +0xb46f4 */
    char pad0b46f6[0xb46fc - 0xb46f6];
    u8 muted;                                       /* +0xb46fc */
    u8 masterLevel;                                 /* +0xb46fd */
    char pad0b46fe[0xb4704 - 0xb46fe];
    u8 bankState[SND_BANK_NUM];                     /* +0xb4704 */
    u8 bankRefs[SND_BANK_NUM];                      /* +0xb4708 */
    s16 bankId[SND_BANK_NUM];                       /* +0xb470c */
    s8 idBank[0x8a];                                /* +0xb4714 */
    u8 seqState;                                    /* +0xb479e */
    char pad0b479f[0xb47b2 - 0xb479f];
    u8 flagA;                                       /* +0xb47b2 */
    u8 flagB;                                       /* +0xb47b3 */
    u8 flagC;                                       /* +0xb47b4 */
    u8 enabled;                                     /* +0xb47b5 */
    u8 busy;                                        /* +0xb47b6 */
    u8 pad0b47b7;
} SoundCtx;

extern SoundCtx *data_0204c234;
extern int **data_0204c024;
extern void *func_020236cc(u32 size, int **heap);
extern void MI_CpuFill8(void *dest, int data, u32 size);
extern void func_02019b68(void);
extern NNSSndHeapHandle func_0201b85c(void *startAddress, u32 size);   /* NNS_SndHeapCreate */
extern void func_02032844(void);

BOOL func_02032db8(void)
{
    SoundCtx *ctx;
    int i;

    if (data_0204c234 != 0) {
        return 1;
    }
    ctx = func_020236cc(sizeof(SoundCtx), data_0204c024);
    data_0204c234 = ctx;
    MI_CpuFill8(ctx, 0, sizeof(SoundCtx));
    func_02019b68();
    ctx->mainHeap = func_0201b85c(ctx->mainArea, sizeof(ctx->mainArea));
    for (i = 0; i < SND_BANK_NUM; i++) {
        ctx->bankHeap[i] = func_0201b85c(ctx->bankArea[i], SND_BANK_SIZE);
        ctx->bankState[i] = 0;
        ctx->bankRefs[i] = 0;
        ctx->bankId[i] = -1;
        ctx->idBank[i] = -1;
    }
    ctx->busy = 0;
    ctx->streamHeap = func_0201b85c(ctx->streamArea, sizeof(ctx->streamArea));
    ctx->effectHeap = func_0201b85c(ctx->effectArea, sizeof(ctx->effectArea));
    func_02032844();
    ctx->fade[0] = 0;
    ctx->fade[1] = 0;
    ctx->fade[2] = 0;
    ctx->scale = 0x1000;
    ctx->pan[0] = 0;
    ctx->pan[1] = 0;
    ctx->seqState = 0;
    ctx->flagB = 0;
    ctx->flagA = 0;
    ctx->muted = 0;
    ctx->masterLevel = 0x7f;
    ctx->seqState = 0;
    ctx->volumeA = 0xa000;
    ctx->volumeB = 0x32000;
    ctx->level = 0x7f;
    ctx->flagC = 0;
    ctx->enabled = 1;
    return 1;
}
