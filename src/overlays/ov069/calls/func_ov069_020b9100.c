/* func_ov069_020b9100 -- walk the 24 recipe entries, price each one this owner can actually make,
 * and report the last matching entry's result id (-1 if none matched).
 *
 * The iteration is driven through the owner's own function pointers at +0xf8 (open, which fills
 * the entry pointer) and +0xfc (close) -- a cursor protocol, not an array walk, so the close runs
 * on every pass including the skipped ones. Taking the entry pointer's address is also why mwcc
 * re-reads it from the frame after every call.
 *
 * An entry is only considered when its group matches owner[0]. Its cost is
 *   owner[2] * entry->baseCost + sum over the 5 ingredient slots of ownerSlot->have * slot.qty,
 * where a slot with a negative id is empty and skipped, and func_ov069_020b90b4 vetoes the entry
 * outright if a required ingredient is missing.
 *
 * The total is rounded UP to a whole 0x1000 unit and then handed on shifted back down. The
 * round-trip is not redundant in the ROM's terms: the value is a Q12 quantity and the callee
 * wants whole units.
 *
 * `entry->kind` picks the presenter: 0 takes the entry itself, 1 and 2 take entry->param and
 * differ only in the flag.
 *
 * Two shapes this needed (both in codegen-cracks.md): the owner's per-slot block is WALKED
 * (owner + 0xdc a pass) because indexing it costs a register and spills `base` onto the stack,
 * while the entry's own slots stay INDEXED -- expressing them as a real array inside the entry
 * struct is what keeps `add r0,r0,r6,lsl #3 ; ldr r0,[r0,#0x28]` instead of a second walking
 * pointer. */

typedef struct {
    void *head;
    void *tail;
    unsigned short count;
    unsigned short offset;
} NNSFndList;

typedef struct {
    int id;
    int qty;
} Ingredient;

typedef struct {
    char reserved[0x14];
    int result;
    int kind;
    int param;
    int group;
    int baseCost;
    Ingredient slots[5];
} Recipe;

extern void *MI_CpuFill8(void *dst, unsigned char v, unsigned int n);
extern void NNS_FndInitList(NNSFndList *list, unsigned short offset);
extern void *NNS_FndGetNextListObject(NNSFndList *list, void *obj);
extern void NNS_FndAppendListObject(NNSFndList *list, void *obj);
extern int func_ov069_020b90b4(int id, int *owner);
extern void func_ov069_020b89f8(int self, Recipe *entry, int units);
extern void func_ov069_020b8a90(int self, int a, int units, int b, int c);
extern void func_ov069_020b8b98(int self, int a, int units, int b, int c);

int func_ov069_020b9100(int self, int *owner) {
    int ret;
    Recipe *entry;
    NNSFndList list;
    char buf[0xa0];
    void *node;
    /* Declaration order IS the callee-saved allocation order here (r4, r5, r6, r7, r8), so this
     * order is what the ROM's ok=r4, i=r5, j=r6, acc=r7, slot=r8 needs. */
    int ok;
    int i;
    int j;
    int acc;
    int base;
    int units;
    char *slot;

    ret = -1;
    entry = 0;
    MI_CpuFill8(buf, 0, 0xa0);
    NNS_FndInitList(&list, 4);

    for (i = 0; i < 0x18; i++) {
        (*(void (**)(Recipe **, int, int, int))(self + 0xf8))(&entry, 0x14, i, 0xe);

        if (entry->group == owner[0]) {
            NNS_FndInitList(&list, 4);
            acc = 0;
            base = owner[2] * entry->baseCost;

            node = NNS_FndGetNextListObject((NNSFndList *)((char *)owner + 0x10), 0);
            *(unsigned short *)buf = *(unsigned short *)node;
            *(unsigned short *)(buf + 2) = *(unsigned short *)((char *)node + 2);
            NNS_FndAppendListObject(&list, buf);

            ok = 1;
            for (j = 0, slot = (char *)owner; j < 5; j++, slot += 0xdc) {
                if (entry->slots[j].id >= 0) {
                    if (func_ov069_020b90b4(entry->slots[j].id, owner) == 0) {
                        ok = 0;
                        break;
                    }
                    acc += *(int *)(slot + 0xe4) * entry->slots[j].qty;
                }
            }

            if (ok != 0) {
                units = (base + acc + 0xfff) / 0x1000 << 12;
                switch (entry->kind) {
                case 0:
                    func_ov069_020b89f8(self, entry, units >> 12);
                    break;
                case 1:
                    func_ov069_020b8a90(self, entry->param, units >> 12, 1, 1);
                    break;
                case 2:
                    func_ov069_020b8b98(self, entry->param, units >> 12, 0, 1);
                    break;
                }
                ret = entry->result;
            }
        }

        (*(void (**)(Recipe **))(self + 0xfc))(&entry);
    }

    return ret;
}
