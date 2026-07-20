/* Add one entry to the owner's running tally, keyed by id.
 *
 * Find the id in the owner's list and accumulate into it; if the id is not there yet,
 * allocate a fresh 0x24-byte node and append it.  Either way the node ends up holding
 * the two running totals, the OR of every flag seen for that id, and the stamp the
 * open callback published.
 *
 * The tally is bracketed by the owner's own callbacks at +0xf8 / +0xfc, which fill and
 * release an info block: info->enabled says whether totalA accumulates at all (when it
 * is clear the total is pinned to -1, i.e. "not available"), info->cap is a per-batch
 * ceiling on totalA, and info->stamp is copied into every node touched.
 *
 * Two ids are special: 0x59 and 0x42 each latch a flag on the owner, and 0x5a's totalB
 * is capped at 12.
 *
 * PARKED ONCE, and the park was one argument short.  It declared four parameters and
 * modelled the fifth as a field of a 0x24-byte local struct, because it read the ROM's
 * `ldr r0, [sp, #0x20]` as a frame access.  It is not: the prologue pushes seven
 * registers (0x1c) and subtracts only 4, so sp+0x20 is above the frame -- it is the
 * INCOMING STACK ARGUMENT.  The only real local is the info pointer at [sp], whose
 * address is taken.  With the arity fixed this matched first try, no codegen tricks.
 *
 * The tell was there from the caller side: OvNNN_TallyScaledSlots does `str r7, [sp]`
 * before the bl, which is a fifth argument and nothing else.
 */
typedef struct {
    char pad00[0x18];
    int enabled;
    int stamp;
    char pad20[4];
    unsigned char cap;
} TallyInfo;

typedef struct {
    int id;
    int totalA;
    int totalB;
    int flags;
    int unk10;
    int stamp;
} TallyNode;

typedef struct {
    char pad00[0x14];
    int list;
    char pad18[0x30 - 0x18];
    int sawId59;
    int sawId42;
    char pad38[0xf8 - 0x38];
    void (*open)(TallyInfo **, int, int, int);
    void (*close)(TallyInfo **);
} TallyOwner;

extern void *NNS_FndGetNextListObject(void *list, void *obj);
extern void NNS_FndAppendListObject(void *list, void *obj);
extern void *NNSi_FndAllocFromDefaultExpHeap(int size);

void func_ov025_02085ba8(TallyOwner *owner, int id, int qtyA, int qtyB, int flag) {
    TallyInfo *info = 0;
    TallyNode *node;

    owner->open(&info, 0x13, id, 0xe);

    if (id == 0x59) owner->sawId59 = 1;
    if (id == 0x42) owner->sawId42 = 1;

    node = (TallyNode *)NNS_FndGetNextListObject(&owner->list, 0);
    if (node) {
        do {
            if (node->id == id) {
                if (info->enabled != 0) node->totalA = node->totalA + qtyA;
                else                    node->totalA = -1;
                node->totalB = node->totalB + qtyB;
                node->flags = node->flags | flag;
                node->stamp = info->stamp;
                break;
            }
            node = (TallyNode *)NNS_FndGetNextListObject(&owner->list, node);
        } while (node);
    }

    if (node == 0) {
        node = (TallyNode *)NNSi_FndAllocFromDefaultExpHeap(0x24);
        node->id = id;
        if (info->enabled == 0) qtyA = -1;
        node->totalA = qtyA;
        node->totalB = qtyB;
        node->flags = flag;
        node->unk10 = 0;
        node->stamp = info->stamp;
        NNS_FndAppendListObject(&owner->list, node);
    }

    if (info->enabled != 0) {
        if (node->totalA > info->cap) node->totalA = info->cap;
    }
    if (node->id == 0x5a) {
        if (node->totalB > 0xc) node->totalB = 0xc;
    }

    owner->close(&info);
}
