/* Answer whether either tracked entry list holds something the panel can show.
 *
 * This is the kind-2 twin of the kind-1 availability query: the panel repaint
 * feeds both results into the same argument slot of its widget update. Lists 0
 * and 2 are the two the panel tracks; when the panel field at +0x58 is set the
 * question degrades to whether either list has a first object at all, and
 * otherwise each list is walked by the filtered helper, list 2 with its
 * alternate mode.
 */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    void *pHead;
    void *pTail;
    u16 nCount;
    u16 nLinkOffset;
} NNSFndList;

typedef struct {
    u8 pad0000[0x480];
    NNSFndList lists[3];    /* +0x480 */
} Ov002PanelSession;

extern Ov002PanelSession *data_ov002_0207f620;

extern int func_ov002_020575d0(void);
extern int func_ov002_0205a754(NNSFndList *pList, int nWhich);
extern int NNS_FndGetNextListObject(NNSFndList *pList, void *pObject);

int func_ov002_0205a7b8(void) {
    Ov002PanelSession *s = data_ov002_0207f620;
    int nResult = 0;

    if (func_ov002_020575d0() != 0) {
        int pEntry = NNS_FndGetNextListObject(&s->lists[0], 0);

        if (pEntry == 0) {
            pEntry = NNS_FndGetNextListObject(&s->lists[2], 0);
        }
        if (pEntry != 0) {
            nResult = 1;
        }
    } else {
        nResult = func_ov002_0205a754(&s->lists[0], 0);
        if (nResult == 0) {
            nResult = func_ov002_0205a754(&s->lists[2], 1);
        }
    }
    return nResult;
}
