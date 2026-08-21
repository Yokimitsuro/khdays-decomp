typedef unsigned short u16;

/* The resource group the track id resolves to: a count and a vector of
 * entries. Same shape the matched func_0202c13c walks. */
typedef struct {
    u16 wPad;                       /* +0x00 */
    u16 wCount;                     /* +0x02 */
    void **apEntry;                 /* +0x04 */
} Ov002EntryGroup;

extern int func_ov002_0207285c(int nSlot);
extern Ov002EntryGroup *func_0202bfa0(int nId);
extern void *func_02028df0(void *pEntry, void *pName);
extern void func_02028e4c(void *pEntry, int nKind, void *pFound, void *pfn,
                          int bFlag);
extern void func_ov002_02072b24(void);

/* Re-apply the element's two named animation bindings.
 *
 * Does nothing for a nameless element. Otherwise it resolves the element's
 * slot to a track id, walks every entry of that id's group, looks the entry up
 * by the element's exact name and re-registers kinds 2 and 1 for it, each with
 * the same callback and the same direction flag - which is set unless the
 * element's last state bit was 1.
 */
void func_ov002_020798a0(char *pElement)
{
    /* The loop index is declared first: it is what the original gives
     * the lowest callee-saved register, and the rest follow from it. */
    int i;
    Ov002EntryGroup *pGroup;
    void *pEntry;
    void *pFound;
    int nId;

    if (*(signed char *)(pElement + 0x1a0) == 0) {
        return;
    }

    nId = func_ov002_0207285c(*(unsigned char *)(pElement + 0x10));
    if (nId < 0) {
        return;
    }

    pGroup = func_0202bfa0((u16)nId);
    i = 0;
    if ((int)pGroup->wCount <= 0) {
        return;
    }

    do {
        pEntry = pGroup->apEntry[i];
        pFound = func_02028df0(pEntry, pElement + 0x1a0);
        func_02028e4c(pEntry, 2, pFound, (void *)func_ov002_02072b24,
                      *(unsigned char *)(pElement + 0x1c2) != 1);
        func_02028e4c(pEntry, 1, pFound, (void *)func_ov002_02072b24,
                      *(unsigned char *)(pElement + 0x1c2) != 1);
        i++;
    } while (i < (int)pGroup->wCount);
}
