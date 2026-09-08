#pragma thumb on

/* Ov022_BindSlotParts -- allocate a slot's parts and bind a sequence to each.
 *
 * Every slot constructor ends here. The part count sits in the slot's second
 * byte, each part is 0x150 bytes, and they come out of the default expanding
 * heap in one block.
 *
 * Each part gets the same sequence the slot plays, the first bound value across
 * all three words of its animation block, a free state, its own index packed
 * into the top five bits of the byte after the state, and a pointer back to the
 * owning slot's tail. The slot's own animation block is bound last, with the
 * second bound value across its three words, and the first is kept beside the
 * parts pointer.
 *
 * The slot and a part carry the same animation block, at 0x08 and at 0x1c: the
 * flag word and the three carried values sit at the same distance in both.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define SEQ_TRACKS 5

/* the block the slot keeps at 0x08 and each part at 0x1c */
struct AnimBlock {
    u16 nFlags;                  /* 0x00 */
    u8 pad02[0xae];
    int aEntryFlags[3];          /* 0xb0 */
};

/* one of the 0x150-byte parts a slot owns */
struct SlotPart {
    u8 pad000[0x1c];
    struct AnimBlock anim;       /* 0x01c */
    u8 pad0d8[0x70];
    void *pOwner;                /* 0x148 */
    u8 nState;                   /* 0x14c */
    u8 nSubFlags : 3;            /* 0x14d */
    u8 nIndex : 5;
    u8 pad14e[2];
};

/* Ov022ActorSlot */
struct ActorSlot {
    u8 pad000;
    u8 nParts;                   /* 0x001 */
    u8 pad002[6];
    struct AnimBlock anim;       /* 0x008 */
    u8 pad0c4[0x54];
    u8 tail[0x50];               /* 0x118 */
    struct SlotPart *pParts;     /* 0x168 */
    int nBound;                  /* 0x16c */
};

extern void *NNSi_FndAllocFromDefaultExpHeap(u32 nSize);
extern void func_0202a634(u16 *pFlags, void *pSeq, int nMode, int nTracks);

void func_ov022_0208b758(struct ActorSlot *pSlot, void *pSeq, int nFirst,
                         int nSecond)
{
    struct AnimBlock *pAnim;
    int i;

    pSlot->pParts = (struct SlotPart *)NNSi_FndAllocFromDefaultExpHeap(
        pSlot->nParts * sizeof(struct SlotPart));
    for (i = 0; i < pSlot->nParts; i++) {
        func_0202a634(&pSlot->pParts[i].anim.nFlags, pSeq, 1, SEQ_TRACKS);
        pAnim = &pSlot->pParts[i].anim;
        pAnim->aEntryFlags[2] = nFirst;
        pAnim->aEntryFlags[1] = pAnim->aEntryFlags[2];
        pAnim->aEntryFlags[0] = pAnim->aEntryFlags[1];
        pSlot->pParts[i].nState = 0;
        pSlot->pParts[i].nIndex = (u8)i;
        pSlot->pParts[i].pOwner = pSlot->tail;
    }
    func_0202a634(&pSlot->anim.nFlags, pSeq, 1, SEQ_TRACKS);
    pSlot->anim.aEntryFlags[2] = nSecond;
    pSlot->anim.aEntryFlags[1] = pSlot->anim.aEntryFlags[2];
    pSlot->anim.aEntryFlags[0] = pSlot->anim.aEntryFlags[1];
    pSlot->nBound = nFirst;
}
