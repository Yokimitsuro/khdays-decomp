/* Allocate and install the slot context, then reset it: the two words at +0/+4
 * to zero and the four id fields to -1. The order of the -1 stores is +0xa,
 * +0xe, +0xc, +0x10 -- not ascending -- and it follows the source.
 *
 * The initialiser takes the ADDRESS OF THE GLOBAL SLOT, not the object: the ROM
 * leaves the pool address in r0 across the store and calls with it. */
extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int size);

typedef struct {
    int dwState;            /* +0 */
    int dwFlags;            /* +4 */
    short wOwner;           /* +8 */
    short wPeerA;           /* +0xa */
    short wPeerC;           /* +0xc */
    short wPeerB;           /* +0xe */
    signed char bStage;     /* +0x10 */
} Ov002SlotContext;

extern void func_ov002_02072cdc(Ov002SlotContext **slot);

extern Ov002SlotContext *data_ov002_0207fa14;

void func_ov002_020734e8(short owner) {
    Ov002SlotContext *ctx =
        (Ov002SlotContext *)NNSi_FndAllocFromDefaultExpHeap(0xc4);

    data_ov002_0207fa14 = ctx;
    func_ov002_02072cdc(&data_ov002_0207fa14);

    ctx->wOwner = owner;
    ctx->dwState = 0;
    ctx->dwFlags = 0;
    ctx->wPeerA = -1;
    ctx->wPeerB = -1;
    ctx->wPeerC = -1;
    ctx->bStage = -1;
}
