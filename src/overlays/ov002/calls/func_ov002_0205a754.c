/* Answer whether the list holds an entry the panel can use.
 *
 * Walks the list and asks the group filter about each entry's key. An entry
 * that passes counts immediately when nAnyTag is set; otherwise it also has to
 * carry a non-zero tag.
 *
 * The two conditions are one short-circuit OR, which is what makes the ROM
 * predicate the tag load rather than branch: it compares nAnyTag, loads the tag
 * under EQ, compares that against zero under EQ too, and a single movne/return
 * pair then serves both arms.
 */
typedef unsigned short u16;

typedef struct {
    void *pHead;
    void *pTail;
    u16 nCount;
    u16 nLinkOffset;
} NNSFndList;

typedef struct {
    u16 nKey;               /* +0x00 */
    u16 nTag;               /* +0x02 */
} Ov002PanelEntry;

extern int func_ov002_0205a714(int nGroup, int nKey);
extern Ov002PanelEntry *NNS_FndGetNextListObject(NNSFndList *pList,
                                                 Ov002PanelEntry *pObject);

int func_ov002_0205a754(NNSFndList *pList, int nAnyTag) {
    Ov002PanelEntry *pEntry = NNS_FndGetNextListObject(pList, 0);

    while (pEntry != 0) {
        if (func_ov002_0205a714(0, pEntry->nKey) != 0) {
            if (nAnyTag != 0 || pEntry->nTag != 0) {
                return 1;
            }
        }
        pEntry = NNS_FndGetNextListObject(pList, pEntry);
    }
    return 0;
}
