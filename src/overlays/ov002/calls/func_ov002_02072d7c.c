/* Publish our own value to the peers: stash it at +0x52 and raise the dirty bit
 * 0x20 at +0x54 so the next send picks it up. Solo sessions have nobody to tell. */
extern int func_02030788(void);

typedef struct {
    char pad0000[0x52];
    unsigned char bValue;   /* +0x52 */
    char pad0053[1];
    unsigned char bFlags;   /* +0x54 */
} Ov002SlotContext;

extern Ov002SlotContext *data_ov002_0207fa14;

void func_ov002_02072d7c(int value) {
    Ov002SlotContext *ctx = data_ov002_0207fa14;

    if (func_02030788() == 0) {
        return;
    }

    ctx->bFlags |= 0x20;
    ctx->bValue = (unsigned char)value;
}
