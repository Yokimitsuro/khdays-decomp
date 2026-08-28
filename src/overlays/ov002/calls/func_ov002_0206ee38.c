typedef signed char s8;
typedef unsigned char u8;

typedef struct Ov002EventSlot {
    char pad0000[0x14];
    s8 bMatchAny;               /* 0x14 */
    s8 nLevel : 7;              /* 0x15 */
    s8 bMuted : 1;
    char pad0016[2];
    struct Ov002EventSlot *pNext;   /* 0x18 */
} Ov002EventSlot;

extern char *data_ov002_0207fa04;   /* the ov002 event context */

/* Puts a slot on the list an event id resolves to.
 *
 * Bit 12 of the id picks which of the context's two banks holds it, and the id
 * with that bit taken back off indexes the bank.  The slot is stamped first:
 * its match byte from the caller, its level set to every bit -- so it matches
 * whatever level is current -- and its muted bit from whether the caller's flag
 * was set at all.
 *
 * Nothing is linked while bit 0 of the bank's flag byte for that id is up.
 * Otherwise the slot goes on the tail of the list, or becomes the list when
 * there is none.  That test is written as a signed `> 0` on a bool the ROM
 * materialises; `!= 0` compiles to a bare tst and comes out eight bytes short.
 *
 * Ghidra models the banks as Ov002EventBank: aSlots at +0x80 and aFlags at
 * +0x100, with the two banks at context +0xc and +0x12c.
 */
void func_ov002_0206ee38(int nEventId, int nMatch, int bMuted, int nUnused,
                         Ov002EventSlot *pSlot)
{
    char *pBank;
    Ov002EventSlot **ppHead;
    Ov002EventSlot *pTail;
    int nAllowed;

    pBank = data_ov002_0207fa04;
    if ((nEventId & 0x1000) != 0) {
        pBank += 0x12c;
        nEventId &= ~0x1000;
    } else {
        pBank += 0xc;
    }

    pSlot->bMatchAny = (s8)nMatch;
    pSlot->nLevel = 0x7f;
    pSlot->bMuted = (s8)(bMuted != 0);

    nAllowed = ((*(u8 *)(pBank + nEventId + 0x100) & 1) == 0);
    if (nAllowed > 0) {
        ppHead = (Ov002EventSlot **)(pBank + 0x80 + nEventId * 4);
        if (*ppHead == 0) {
            *ppHead = pSlot;
        } else {
            pTail = *ppHead;
            while (pTail->pNext != 0) {
                pTail = pTail->pNext;
            }
            pTail->pNext = pSlot;
        }
    }
}
