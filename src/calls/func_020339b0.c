/* func_020339b0 -- release a sound-data bank, MAIN. The game's sound context (data_0204c234) keeps
 * four sound heaps of 0x1c00 bytes carved from its +0x5e4a0 area, each with a state (+0xb4704),
 * a reference count (+0xb4708) and the id loaded in it (+0xb470c), plus the bank each id sits in
 * (+0xb4714). A negative id rebuilds all four heaps, provided every bank holds the same id and the
 * first one is loaded (state >= 2). Otherwise, unless the context is busy (+0xb47b6), the id's bank
 * loses a reference and, at zero, is cleared and forgotten; the id is unmapped either way. */
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
extern void func_0201b8e4(NNSSndHeapHandle heap);   /* NNS_SndHeapClear */

BOOL func_020339b0(int id)
{
    SoundCtx *ctx = data_0204c234;
    int i;

    if (id < 0) {
        for (i = 0; i < SND_BANK_NUM; i++) {
            if (ctx->bankId[0] != ctx->bankId[i]) {
                return 0;
            }
        }
        if (ctx->bankState[0] >= 2) {
            func_0201b8cc(ctx->bankHeap[0]);
            for (i = 0; i < SND_BANK_NUM; i++) {
                ctx->bankHeap[i] = func_0201b85c(ctx->bankArea[i], SND_BANK_SIZE);
                ctx->bankState[i] = 0;
                ctx->bankRefs[i] = 0;
                ctx->bankId[i] = -1;
                ctx->idBank[i] = -1;
            }
            ctx->busy = 0;
            return 1;
        }
    } else {
        int bank = ctx->idBank[id];

        if (ctx->busy) {
            return 0;
        }
        if (bank < 0) {
            return 1;
        }
        if (ctx->bankState[bank] >= 2) {
            if (--ctx->bankRefs[bank] == 0) {
                ctx->bankState[bank] = 0;
                func_0201b8e4(ctx->bankHeap[bank]);
                ctx->bankId[bank] = -1;
            }
            ctx->idBank[id] = -1;
            return 1;
        }
    }
    return 0;
}
