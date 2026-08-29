typedef unsigned short u16;

/* The resource group the track id resolves to: a count and a vector of
 * entries. Same shape func_ov002_020798a0 walks. */
typedef struct {
    u16 wPad;                       /* +0x00 */
    u16 wCount;                     /* +0x02 */
    void **apEntry;                 /* +0x04 */
} Ov002EntryGroup;

extern Ov002EntryGroup *func_0202bfa0(int nId);
/* Hands back the next binding of the entry that matches, walking the cursor
   the caller passes; zero once there are no more. */
extern void *func_ov002_020713cc(void *pEntry, void *pName, void *pFilter,
                                 int *pCursor);
extern void func_02028e4c(void *pEntry, int nKind, void *pFound, void *pfn,
                          int bFlag);
extern void func_ov002_02072b24(void);

/* Re-apply every matching animation binding across a whole track group.
 *
 * Where func_ov002_020798a0 re-registers one element's single named binding,
 * this walks each entry of the group and keeps asking for the next match until
 * the entry runs out, re-registering kinds 2 and 1 for each one with the same
 * callback and the caller's direction flag.
 */
void func_ov002_02072aa0(void *pName, void *pFilter, int bFlag, int nId)
{
    void *pEntry;
    void *pFound;
    int i;
    Ov002EntryGroup *pGroup;
    int nCursor;

    pGroup = func_0202bfa0((u16)nId);
    for (i = 0; i < (int)pGroup->wCount; i++) {
        pEntry = pGroup->apEntry[i];
        nCursor = 0;
        for (;;) {
            pFound = func_ov002_020713cc(pEntry, pName, pFilter, &nCursor);
            if (pFound == 0) {
                break;
            }
            func_02028e4c(pEntry, 2, pFound, (void *)func_ov002_02072b24,
                          bFlag);
            func_02028e4c(pEntry, 1, pFound, (void *)func_ov002_02072b24,
                          bFlag);
            nCursor++;
        }
    }
}
