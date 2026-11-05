
/* One row of the marker table, sixteen bytes. The limit is a four bit field:
 * the ROM extracts it with a shift pair rather than a mask. */

#include "nitro/types.h"

typedef struct Ov002MarkerRow {
    u8 bId;                             /* +0x0 */
    u8 nMaxOut : 4;                     /* +0x1 low nibble: the most of the row's class out at once, 0 no limit */
    u8 nHigh : 4;
    char pad02[3];
    s8 nParam;                          /* +0x5 */
    char pad06[10];
} Ov002MarkerRow;

extern char *data_ov002_0207fa14;

extern int *Ov107_GetActorManager(void);
extern u8 Ov107_AllocSortedEntry(int nHandle, int nId, int nLevel, int nParam);
extern void Ov107_ContainerNode_Finalize(int nHandle);
extern void Ov107_SetLookupByte(int nHandle, int nSlot, int nMaxOut);
extern int Ov002_GetMarkerEnemyLevel(Ov002MarkerRow *pRow);
extern int Ov002_GetStateWord(void);

/* Add one row to the marker list, or flush the whole list.
 *
 * A non-negative index appends: the row's marker is registered with the
 * renderer and the returned handle and the row index go into the next pair of
 * the list, which then grows by one. In state 2000 the marker goes in flat,
 * with no level and no extra parameter. A negative index instead drops the
 * list's owner and walks every pair already in it, handing each handle back
 * with its row's limit of actors out at once.
 *
 * Codegen note: the pair's index byte has to be stored inside both branches,
 * not once after the if. mwcc merges the two identical stores into one and
 * lets each branch build the address into its own stack slot, which is what
 * the ROM does; hoisting the store out of the branches loses eight bytes. The
 * guard on the pair count also has to read it into an int first, or the u8
 * comparison folds to a test against zero and the signed branch is lost.
 */
void Ov002_UpdateSlotLookup(int nIndex)
{
    char *pCtx;
    char *pTable;
    Ov002MarkerRow *pRow;
    int nHandle;
    int nCount;
    int nLevel;
    int nTotal;
    int i;
    int k;

    pCtx = data_ov002_0207fa14;
    pTable = *(char **)(pCtx + 4);
    nHandle = *Ov107_GetActorManager();

    if (nIndex >= 0) {
        nCount = *(u8 *)(pCtx + 0x51);
        pRow = (Ov002MarkerRow *)(*(char **)(pTable + 4)) + nIndex;
        nLevel = Ov002_GetMarkerEnemyLevel(pRow);
        if (Ov002_GetStateWord() == 2000) {
            *(u8 *)(*(char **)(pCtx + 0x4c) + nCount * 2 + 1) =
                Ov107_AllocSortedEntry(nHandle, pRow->bId, 0, 0);
            *(u8 *)(*(char **)(pCtx + 0x4c) + nCount * 2) = (u8)nIndex;
        } else {
            *(u8 *)(*(char **)(pCtx + 0x4c) + nCount * 2 + 1) =
                Ov107_AllocSortedEntry(nHandle, pRow->bId, nLevel,
                                    pRow->nParam);
            *(u8 *)(*(char **)(pCtx + 0x4c) + nCount * 2) = (u8)nIndex;
        }
        *(u8 *)(pCtx + 0x51) = *(u8 *)(pCtx + 0x51) + 1;
        return;
    }

    Ov107_ContainerNode_Finalize(nHandle);
    i = 0;
    nTotal = *(u8 *)(pCtx + 0x51);
    if (nTotal > 0) {
        k = 0;
        do {
            Ov107_SetLookupByte(nHandle,
                                *(s8 *)(*(char **)(pCtx + 0x4c) + k + 1),
                                ((Ov002MarkerRow *)
                                 (*(char **)(pTable + 4)))
                                    [*(s8 *)(*(char **)(pCtx + 0x4c) + k)]
                                        .nMaxOut);
            i++;
            k += 2;
        } while (i < *(u8 *)(pCtx + 0x51));
    }
}
