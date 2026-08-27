/*
 * Stamps an entry with its kind, its id and its slot.
 *
 * A negative index means the caller does not know which value it wants and the
 * resolver is asked, handing it the index to fill in as well; otherwise the
 * value comes straight out of the lookup table. Either way the entry that
 * value names is fetched and the kind is written.
 *
 * The id is only written when it is not the empty id, and while the boot-mode
 * flag is set an entry that carries the second flag loses its first. The slot
 * is only written when the caller gave a real one.
 *
 * One thing here is load-bearing rather than style. The table read groups as
 * (base + index) indexed by the field offset, not base indexed by their sum.
 * THUMB's signed byte load has no immediate form, so the offset needs a
 * register either way, and the grouping decides which of the two sums it holds.
 *
 * THUMB.
 */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov002Entry {
    char pad00[1];
    u8 nSlot;
    char pad02[1];
    u8 nKind;
    u16 nFlags;
} Ov002Entry;

extern s8 *data_ov002_0207fa10;
extern u8 data_0204c240;

extern void func_ov002_02072770(int nOwner, int *pIndex, int *pValue);
extern Ov002Entry *func_ov002_02071420(int nOwner, int nValue);

int func_ov002_02072194(int nIndex, int nOwner, int nId, int nKind, s8 nSlot)
{
    int nValue;
    Ov002Entry *pEntry;

    if (nIndex < 0) {
        func_ov002_02072770(nOwner, &nIndex, &nValue);
    } else {
        nValue = (data_ov002_0207fa10 + nIndex)[0x2f];
    }

    pEntry = func_ov002_02071420(nOwner, nValue);
    pEntry->nKind = (u8)nKind;
    if (nId != 0xffff) {
        pEntry->nFlags = (u16)nId;
        if ((data_0204c240 & 4) != 0 && (pEntry->nFlags & 2) != 0) {
            pEntry->nFlags = (u16)(pEntry->nFlags & ~1);
        }
    }
    if (nSlot >= 0) {
        pEntry->nSlot = (u8)nSlot;
    }
    return 1;
}
