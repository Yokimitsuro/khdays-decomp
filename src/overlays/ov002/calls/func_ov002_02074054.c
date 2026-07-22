/* Same bit-1 update as func_ov002_02074024, but on whichever object the current
 * selection resolves to rather than a numbered slot. The resolver hands back a
 * pointer to the slot, so the object needs one more dereference.
 *
 * The resolver takes the CONSTANT -1 ("current"), not the context -- the -1 built
 * for the handle comparison is what is still in r0 at the call. */
extern void **OS_IsThreadAvailable_0x020c9848(int which);

typedef struct {
    char pad0000[0x40];
    unsigned int dwFlags;       /* +0x40 */
} Ov002SlotObject;

typedef struct {
    char pad0000[0x18];
    int nHandle;                /* +0x18, -1 = none */
} Ov002SlotContext;

extern Ov002SlotContext *data_ov002_0207fa14;

void func_ov002_02074054(int flag) {
    Ov002SlotContext *ctx = data_ov002_0207fa14;
    Ov002SlotObject *obj;

    if (ctx == 0) {
        return;
    }

    if (ctx->nHandle == -1) {
        return;
    }

    obj = (Ov002SlotObject *)*OS_IsThreadAvailable_0x020c9848(-1);
    obj->dwFlags = (obj->dwFlags & ~2) | ((flag & 1) << 1);
}
