/* func_02033788 -- acquire the sound-data bank for `id`, loading `dataId` (with its wave data at
 * dataId + 0x25) asynchronously through func_0201f750, MAIN. Returns whether the bank is ready
 * (state >= 2). A negative id claims the whole 0x7000-byte area as one heap when no id holds a bank
 * (all four banks are marked loading with dataId and the context becomes busy). Otherwise an id
 * already mapped just reports its bank; a busy context refuses; a bank already holding dataId gains
 * a reference; else the last free bank is taken and loading starts. */
typedef unsigned char u8;
typedef signed char s8;
typedef short s16;
typedef int BOOL;
typedef struct NNSSndHeap *NNSSndHeapHandle;

#define SND_BANK_NUM 4
#define SND_BANK_SIZE 0x1c00

typedef struct SoundCtx {
    char pad000000[0x5e4a0];
    char bankArea[SND_BANK_NUM][SND_BANK_SIZE];     /* +0x5e4a0 */
    char pad0654a0[0xb04a4 - 0x654a0];
    NNSSndHeapHandle bankHeap[SND_BANK_NUM];        /* +0xb04a4 */
    char pad0b04b4[0xb4704 - 0xb04b4];
    u8 bankState[SND_BANK_NUM];                     /* +0xb4704 */
    u8 bankRefs[SND_BANK_NUM];                      /* +0xb4708 */
    s16 bankId[SND_BANK_NUM];                       /* +0xb470c */
    s8 idBank[0xa2];                                /* +0xb4714 */
    u8 busy;                                        /* +0xb47b6 */
} SoundCtx;

extern SoundCtx *data_0204c234;
extern NNSSndHeapHandle func_0201b85c(void *startAddress, unsigned int size);   /* NNS_SndHeapCreate */
extern void func_0201b8cc(NNSSndHeapHandle heap);   /* NNS_SndHeapDestroy */
extern void func_0201f750(unsigned short dataId, unsigned short waveId, NNSSndHeapHandle heap, u8 *pState);

BOOL func_02033788(int id, int dataId)
{
    SoundCtx *ctx = data_0204c234;
    int i;

    if (id < 0) {
        if (ctx->idBank[0] >= 0) {
            return ctx->bankState[0] >= 2;
        }
        for (i = 0; i < SND_BANK_NUM; i++) {
            if (ctx->idBank[i] >= 0) {
                return 0;
            }
        }
        for (i = 0; i < SND_BANK_NUM; i++) {
            ctx->idBank[i] = i;
            ctx->bankId[i] = (s16)dataId;
            ctx->bankState[i] = 1;
            ctx->bankRefs[i] = 1;
            func_0201b8cc(ctx->bankHeap[i]);
        }
        ctx->bankHeap[0] = func_0201b85c(ctx->bankArea[0], SND_BANK_NUM * SND_BANK_SIZE);
        func_0201f750((unsigned short)dataId, (unsigned short)(dataId + 0x25), ctx->bankHeap[0], &ctx->bankState[0]);
        ctx->busy = 1;
        return 0;
    } else {
        int free;
        int bank = ctx->idBank[id];

        if (bank < 0) {
            free = -1;
            if (ctx->busy) {
                return 0;
            }
            for (i = 0; i < SND_BANK_NUM; i++) {
                if (ctx->bankState[i] == 0) {
                    free = i;
                } else if (dataId == ctx->bankId[i]) {
                    ctx->idBank[id] = i;
                    ctx->bankRefs[i]++;
                    return ctx->bankState[i] >= 2;
                }
            }
            ctx->bankId[free] = dataId;
            ctx->bankState[free] = 1;
            ctx->bankRefs[free]++;
            ctx->idBank[id] = free;
            func_0201f750((unsigned short)dataId, (unsigned short)(dataId + 0x25), ctx->bankHeap[free], &ctx->bankState[free]);
            return 0;
        }
        return ctx->bankState[bank] >= 2;
    }
}
