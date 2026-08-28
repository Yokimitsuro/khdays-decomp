typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;

extern char *data_ov002_0207fa04;   /* the ov002 event context */

/* Hands back the level the current session is at, or -1 when none is open. */
extern int func_ov002_0206ba48(void);

/* Pops the head of the event queue and runs its handler.
 *
 * Bit 4 of the context's first halfword says an event is waiting; with it
 * clear nothing moves and the answer is -1.  Otherwise the id in the first
 * handle goes out through pnEventId, the bit is cleared, the four handles
 * shift down by one, the last becomes -1 and the count goes to zero.
 *
 * The id then picks a bank the same way Ov002_CloseEvent does -- bit 12
 * selects the second one and is masked off the index -- except that this walks
 * the slot list at +0x80 of the bank rather than the handler array at its top.
 * The list is followed to the first entry that either matches any level or
 * matches the one the session is at; its first field is a callback and is run
 * with the entry itself, and its answer becomes this one's.  An empty slot, or
 * a list with no such entry, answers zero.
 *
 * Ghidra models the entries as Ov002EventSlot: pfnRun at +0, bMatchAny at
 * +0x14, the level in the low seven bits of bLevelAndMuted at +0x15, and pNext
 * at +0x18.
 */
int func_ov002_0206ec54(int *pnEventId)
{
    char *pCtx;
    char *pSlots;
    char *pEntry;
    int nEventId;
    int nLevel;
    int i;

    pCtx = data_ov002_0207fa04;
    nEventId = *(s16 *)(pCtx + 2);
    if ((*(u16 *)pCtx & 0x10) == 0) {
        return -1;
    }

    *pnEventId = nEventId;
    *(u16 *)pCtx = (u16)(*(u16 *)pCtx & ~0x10);
    for (i = 0; i < 3; i++) {
        ((s16 *)pCtx)[i + 1] = ((s16 *)pCtx)[i + 2];
    }
    *(s16 *)(pCtx + 8) = -1;
    *(u8 *)(pCtx + 0xa) = 0;

    if ((nEventId & 0x1000) != 0) {
        pSlots = pCtx + 0x12c;
        nEventId &= ~0x1000;
    } else {
        pSlots = pCtx + 0xc;
    }
    pEntry = *(char **)(pSlots + nEventId * 4 + 0x80);
    if (pEntry == 0) {
        return 0;
    }

    nLevel = func_ov002_0206ba48();
    while (pEntry != 0) {
        if (*(int *)pEntry == 0) {
            pEntry = *(char **)(pEntry + 0x18);
        } else {
            if (*(s8 *)(pEntry + 0x14) < 0) {
                break;
            }
            if (((*(s8 *)(pEntry + 0x15) << 25) >> 25) == nLevel) {
                break;
            }
            pEntry = *(char **)(pEntry + 0x18);
        }
    }
    if (pEntry == 0) {
        return 0;
    }
    return (*(int (**)(char *))pEntry)(pEntry);
}
