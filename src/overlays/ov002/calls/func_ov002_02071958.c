/* Tear the link context down: unhook it, free its eight per-seat buffers at
 * +0x34, then free the context itself and clear the global slot. The unhook call
 * takes the ADDRESS of the slot, which is what the pool load left in r0. */
extern void func_ov002_02071ae0(void **slot);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

typedef struct {
    char pad0000[0x34];
    void *buffers[8];       /* +0x34 */
} Ov002LinkCtx;

extern Ov002LinkCtx *data_ov002_0207fa10;

void func_ov002_02071958(void) {
    Ov002LinkCtx *ctx = data_ov002_0207fa10;
    int i;

    func_ov002_02071ae0((void **)&data_ov002_0207fa10);

    for (i = 0; i < 8; i++) {
        if (ctx->buffers[i] != 0) {
            NNSi_FndFreeFromDefaultHeap(ctx->buffers[i]);
            ctx->buffers[i] = 0;
        }
    }

    NNSi_FndFreeFromDefaultHeap(data_ov002_0207fa10);
    data_ov002_0207fa10 = 0;
}
