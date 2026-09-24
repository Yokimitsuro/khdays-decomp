#pragma thumb on
typedef unsigned char u8;
typedef signed char s8;
typedef short s16;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int BOOL;
typedef struct NNSSndHeap *NNSSndHeapHandle;
typedef struct { void *player; } NNSSndHandle;
typedef struct { void *player; } NNSSndStrmHandle;

#define SND_BANK_NUM 4
#define SND_BANK_SIZE 0x1c00

typedef struct SoundNode {
    struct SoundNode *next;             /* +0x00 */
    struct SoundNode *prev;             /* +0x04 */
    char pad08[0x16 - 8];
    u16 id;                             /* +0x16 */
    int pad18;
    NNSSndHandle handle;                /* +0x1c */
} SoundNode;

typedef struct SoundCtx {
    char arc[0x94];                                 /* +0x00000: NNSSndArc */
    void *waveHeap;                                 /* +0x00094 */
    void *waveHeapCur;                              /* +0x00098 */
    int waveState;                                  /* +0x0009c */
    char mainArea[0x5e400];                         /* +0x000a0 */
    char bankArea[SND_BANK_NUM][SND_BANK_SIZE];     /* +0x5e4a0 */
    char streamArea[0x4b000];                       /* +0x654a0 */
    NNSSndHeapHandle mainHeap;                      /* +0xb04a0 */
    NNSSndHeapHandle bankHeap[SND_BANK_NUM];        /* +0xb04a4 */
    NNSSndHeapHandle streamHeap;                    /* +0xb04b4 */
    char effectArea[0x4000];                        /* +0xb04b8 */
    NNSSndHeapHandle effectHeap;                    /* +0xb44b8 */
    NNSSndStrmHandle strm[2];                       /* +0xb44bc */
    NNSSndHandle seHandle;                          /* +0xb44c4 */
    NNSSndHandle bgmHandle;                         /* +0xb44c8 */
    int fade[3];                                    /* +0xb44cc */
    int scale;                                      /* +0xb44d8 */
    int pan[2];                                     /* +0xb44dc */
    SoundNode node[16];                             /* +0xb44e4 */
    SoundNode *freeNode;                            /* +0xb46e4 */
    int pad0b46e8;
    int volumeA;                                    /* +0xb46ec */
    int volumeB;                                    /* +0xb46f0 */
    u16 level;                                      /* +0xb46f4 */
    s16 curBgm;                                     /* +0xb46f6 */
    s16 nextBgm;                                    /* +0xb46f8 */
    u16 bgmFlags;                                   /* +0xb46fa */
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
extern const char data_020429ec[];      /* default sound archive path */
extern void func_0203358c(void);
extern void func_02019f6c(int mode);
extern void func_02019b68(void);
extern void func_0201b168(void *arc, const char *path, NNSSndHeapHandle heap, int bSymbolLoad);   /* NNS_SndArcInit */
extern void func_0201b824(int prio);
extern void func_0201c524(NNSSndHeapHandle heap);
extern void func_0201a064(NNSSndHandle *handle);           /* NNS_SndHandleInit */
extern void MI_CpuFill8(void *dest, int data, u32 size);
extern void func_0201c8f4(u32 threadPrio, NNSSndHeapHandle heap);   /* NNS_SndArcStrmInit */
extern void func_0201cbc4(NNSSndStrmHandle *handle);       /* NNS_SndStrmHandleInit */
extern int func_0201bc20(u32 waveId, NNSSndHeapHandle heap);
extern void *func_0201ba08(NNSSndHeapHandle heap);

/* func_020333c8 -- start the sound system on a sound archive, MAIN. `path` (default
 * data_020429ec) is opened into the context's archive with the main heap; the player priority,
 * the main heap's groups and the SE/BGM handles are set up; the 16 sound nodes are cleared,
 * chained into a doubly linked free list (ids 6..21, each with its own handle); streaming starts
 * on the effect heap (priority 10) with its two stream handles; the BGM slots are emptied, wave
 * archive 0x25 is loaded and the main heap's current level is recorded twice with the wave state
 * reset to -1. */
void func_020333c8(const char *path)
{
    SoundCtx *ctx = data_0204c234;
    int i;

    if (path == 0) {
        path = data_020429ec;
    }
    func_0203358c();
    func_02019f6c(0);
    func_02019b68();
    func_0201b168(ctx->arc, path, ctx->mainHeap, 0);
    func_0201b824(0x400);
    func_0201c524(ctx->mainHeap);
    func_0201a064(&ctx->seHandle);
    func_0201a064(&ctx->bgmHandle);
    MI_CpuFill8(ctx->node, 0, sizeof(ctx->node));
    for (i = 0; i < 16; i++) {
        ctx->node[i].next = (i < 15) ? &ctx->node[i + 1] : 0;
        ctx->node[i].prev = (i > 0) ? &ctx->node[i - 1] : 0;
        ctx->node[i].id = i + 6;
        func_0201a064(&ctx->node[i].handle);
    }
    ctx->freeNode = &ctx->node[0];
    func_0201c8f4(10, ctx->effectHeap);
    func_0201cbc4(&ctx->strm[0]);
    func_0201cbc4(&ctx->strm[1]);
    ctx->curBgm = -1;
    ctx->nextBgm = -1;
    ctx->bgmFlags = 0;
    func_0201bc20(0x25, ctx->mainHeap);
    ctx->waveHeap = func_0201ba08(data_0204c234->mainHeap);
    ctx->waveHeapCur = ctx->waveHeap;
    ctx->waveState = -1;
}
