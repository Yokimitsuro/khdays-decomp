/* Add one entry to the owner's SECONDARY tally, keyed by id.
 *
 * Same idea as OvNNN_AddToTally but over the list at owner+8 rather than owner+0x14,
 * and with the bracketing callbacks run AFTER the accumulation instead of around it --
 * this one only needs the info block for its cap, so it fetches it last.
 *
 * Node layout differs too: id at +0, the OR of the flags at +8, totalA at +0x10 and
 * totalB at +0x14.  totalA is clamped to info->cap, totalB to 99 unconditionally --
 * there is no info->enabled gate here, so unlike AddToTally a total is never pinned
 * to -1.
 *
 * The fifth argument arrives on the stack (`ldr r0, [sp, #0x20]`, above a 0x20-byte
 * frame).  Only the info pointer is a real local.
 *
 * The two clamps are spelled DIFFERENTLY on purpose, and that is the whole match:
 *  - totalA clamps in place, `if (a > cap) a = cap;`, which mwcc emits as a predicated
 *    STORE (`strgt r1, [r4, #0x10]`);
 *  - totalB clamps through a temporary, which emits a predicated MOVE and then an
 *    unconditional store (`movgt r0, #0x63 ; str r0, [r4, #0x14]`).
 * Writing both the same way puts a `strgt` where the ROM has `str` and the function
 * misses by one byte at 0xff.
 */
typedef struct {
    char pad00[0x24];
    unsigned char cap;
} TallyInfo2;

typedef struct {
    int id;
    char pad04[4];
    int flags;
    int unk0c;
    int totalA;
    int totalB;
} TallyNode2;

typedef struct {
    char pad00[8];
    int list;
    char pad0c[0xf8 - 0xc];
    void (*open)(TallyInfo2 **, int, int, int);
    void (*close)(TallyInfo2 **);
} TallyOwner2;

extern void *NNS_FndGetNextListObject(void *list, void *obj);
extern void NNS_FndAppendListObject(void *list, void *obj);
extern void *NNSi_FndAllocFromDefaultExpHeap(int size);

void func_ov005_0204ef70(TallyOwner2 *owner, int id, int qtyA, int qtyB, int flag) {
    TallyInfo2 *info = 0;
    TallyNode2 *node;
    int total;

    node = (TallyNode2 *)NNS_FndGetNextListObject(&owner->list, 0);
    if (node) {
        do {
            if (node->id == id) {
                node->totalA = node->totalA + qtyA;
                node->totalB = node->totalB + qtyB;
                node->flags = node->flags | flag;
                break;
            }
            node = (TallyNode2 *)NNS_FndGetNextListObject(&owner->list, node);
        } while (node);
    }

    if (node == 0) {
        node = (TallyNode2 *)NNSi_FndAllocFromDefaultExpHeap(0x24);
        node->id = id;
        node->totalA = qtyA;
        node->totalB = qtyB;
        node->flags = flag;
        node->unk0c = 0;
        NNS_FndAppendListObject(&owner->list, node);
    }

    owner->open(&info, 0x13, id, 0xe);
    if (node->totalA > info->cap) {
        node->totalA = info->cap;
    }
    owner->close(&info);

    total = node->totalB;
    if (total > 0x63) {
        total = 0x63;
    }
    node->totalB = total;
}
