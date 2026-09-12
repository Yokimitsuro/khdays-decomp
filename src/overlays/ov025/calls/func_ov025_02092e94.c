/* func_ov025_02092e94 -- Ov008_AssignFreeListId: give a new node the lowest free
 * one-byte id in the context's id list (ids start at 1) and link it in at its
 * sorted position: before the first node whose id is not the next expected one,
 * or appended at the end.  Returns the id, or 0 when all 255 are taken.
 */
typedef unsigned char u8;

typedef struct NNSFndList {
    u8 pad[12];
} NNSFndList;

typedef struct Ov008IdListOwner {
    u8         pad_0000[0x1e7c];
    NNSFndList list;          /* 0x1e7c */
} Ov008IdListOwner;

#define ID_FIRST 1
#define ID_LAST  0xff

extern void *NNS_FndGetNextListObject(NNSFndList *pList, void *pObject);
extern void NNS_FndInsertListObject(NNSFndList *pList, void *pTarget, void *pObject);
extern void NNS_FndAppendListObject(NNSFndList *pList, void *pObject);

u8 func_ov025_02092e94(Ov008IdListOwner *pOwner, u8 *pNode)
{
    u8 *pObject;
    u8 nId = ID_FIRST;

    pObject = NNS_FndGetNextListObject(&pOwner->list, 0);

    while (pObject != 0) {
        if (nId != *pObject) {
            *pNode = nId;
            NNS_FndInsertListObject(&pOwner->list, pObject, pNode);
            break;
        }
        if (nId == ID_LAST) {
            return 0;
        }
        nId++;
        pObject = NNS_FndGetNextListObject(&pOwner->list, pObject);
    }
    if (pObject == 0) {
        *pNode = nId;
        NNS_FndAppendListObject(&pOwner->list, pNode);
    }
    return nId;
}
