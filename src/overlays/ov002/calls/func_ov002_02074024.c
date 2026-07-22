/* Set or clear bit 1 of slot `index`'s flag word from bit 0 of `flag`. Needs a
 * live handle and an occupied slot; both missing cases are silent. */
typedef struct {
    char pad0000[0x40];
    unsigned int dwFlags;       /* +0x40 */
} Ov002SlotObject;

typedef struct {
    char pad0000[0x18];
    int nHandle;                /* +0x18, -1 = none */
    Ov002SlotObject *slots[1];  /* +0x1c */
} Ov002SlotContext;

extern Ov002SlotContext *data_ov002_0207fa14;

void func_ov002_02074024(int index, int flag) {
    Ov002SlotContext *ctx = data_ov002_0207fa14;
    Ov002SlotObject *obj;

    if (ctx->nHandle == -1) {
        return;
    }

    obj = ctx->slots[index];
    if (obj == 0) {
        return;
    }

    obj->dwFlags = (obj->dwFlags & ~2) | ((flag & 1) << 1);
}
