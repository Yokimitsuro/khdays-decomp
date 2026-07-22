/* The second parameter is FORWARDED, not used: it arrives in r1 and is handed to
 * the callee untouched, so it costs no instruction and is invisible in the
 * disassembly. Its only trace is that r1 is unavailable as a scratch register,
 * which shifts every other allocation up by one. */
/* Fire slot `index`'s notify hook, if everything along the way is present: the
 * context must hold a live handle at +0x18, the slot at +0x1c must be occupied,
 * and the occupant must carry a hook at +0x18. The hook takes the occupant. */
typedef struct {
    char pad0000[0x18];
    void *pHook;            /* +0x18 */
} Ov002SlotObject;

typedef struct {
    char pad0000[0x18];
    int nHandle;            /* +0x18, -1 = none */
    Ov002SlotObject *slots[1];  /* +0x1c */
} Ov002SlotContext;

extern Ov002SlotContext *data_ov002_0207fa14;

void func_ov002_02073ffc(int index, int arg) {
    Ov002SlotContext *ctx = data_ov002_0207fa14;
    Ov002SlotObject *obj;

    if (ctx->nHandle == -1) {
        return;
    }

    obj = ctx->slots[index];
    if (obj == 0) {
        return;
    }

    if (obj->pHook == 0) {
        return;
    }

    ((void (*)(Ov002SlotObject *, int))obj->pHook)(obj, arg);
}
