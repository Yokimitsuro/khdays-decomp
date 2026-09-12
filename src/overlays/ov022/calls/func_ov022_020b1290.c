/* Ov022_BuildResNodeSet -- lay the request's five node groups out behind its
 * resource and load each node.
 *
 * Every group's node count comes from the resource's member of that index.
 * With no nodes at all the set is cleared. Otherwise the cursor starts at the
 * resource plus its size rounded up to four plus what is already used, and
 * each group with nodes takes count pointers there (the used size grows by
 * them). Then every node of every group is given the next free spot, sized
 * by its region table, and loaded there; group 3 alone loads with the
 * texture of the owner's seventh member. Each group's count is recorded and
 * the set's tag is the request's count plus seven.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* Ov022ResNodeSet: what this function fills (embedded at request+4) */
struct ResNodeSet {
    u16 anCounts[5];             /* 0x00 nodes per group */
    u16 nTag;                    /* 0x0a request count + 7 */
    u8 pad0c[4];
    void **apNodes[5];           /* 0x10 per group: count node pointers */
};

struct ResOwner {
    u8 pad00[0xc];
    void *pArchive;              /* 0x0c */
};

struct ResInfo {
    u8 pad00[0x74];
    struct ResOwner *pOwner;     /* 0x74 */
    void *pRegion;               /* 0x78 */
};

/* Ov022SyncRequest (the loading side of it) */
struct LoadRequest {
    u8 pad00[1];
    u8 nCount;                   /* 0x01 */
    u8 pad02[0x26];
    struct ResInfo *pInfo;       /* 0x28 */
    u8 *pArchive;                /* 0x2c */
    u16 nSize;                   /* 0x30 */
    u8 pad32[2];
    u16 nUsed;                   /* 0x34 */
};

#define GROUP_COUNT 5
#define TEX_GROUP 3
#define TEX_MEMBER 7
#define TAG_BIAS 7

extern void *func_020255d4(void *pArchive, int nGroup, int nIndex);   /* Archive_GetMember */
extern int func_ov022_020b1078(void *pMember);                        /* node count of a member */
extern void MI_CpuFill8(void *pDst, int nValue, u32 nSize);
extern u8 *func_020170c8(void *pMember, int nIndex);
extern u32 NTRi_GetRegionTableSize(u8 *pNode, void *pRegion);
extern void *func_02017088(void *pResource);                          /* NNS_G3dGetTex */
extern void func_02014abc(void *pDst, u8 *pNode, void *pRegion, void *pTex);

void func_ov022_020b1290(struct LoadRequest *pReq, struct ResNodeSet *pSet)
{
    int nGroup;
    int nTotal;
    int nNodes;
    int nIndex;
    int nUsed;
    u32 nSize;
    u8 *pCursor;
    u8 *pNext;
    void *pMember;
    u8 *pNode;
    void *pTex;
    struct ResInfo *pInfo;
    u32 nTableSize;

    nTotal = 0;
    for (nGroup = 0; nGroup < GROUP_COUNT; nGroup++) {
        nTotal += func_ov022_020b1078(func_020255d4(pReq->pArchive, nGroup, 0));
    }
    if (nTotal > 0) {
        nSize = pReq->nSize;
        nUsed = pReq->nUsed;
        if ((pReq->nSize & 3) != 0) {
            nSize += 4 - (nSize & 3);
        }
        nUsed = nSize + nUsed;
        pCursor = pReq->pArchive + nUsed;
        pNext = pCursor;
        for (nGroup = 0; nGroup < GROUP_COUNT; nGroup++) {
            nNodes = func_ov022_020b1078(func_020255d4(pReq->pArchive, nGroup, 0));
            if (nNodes > 0) {
                pNext += nNodes * 4;
                pSet->apNodes[nGroup] = (void **)pCursor;
                pCursor += nNodes * 4;
                pReq->nUsed += nNodes * 4;
            } else {
                pSet->apNodes[nGroup] = 0;
            }
        }
    } else {
        MI_CpuFill8(pSet, 0, sizeof(struct ResNodeSet));
    }
    for (nGroup = 0; nGroup < GROUP_COUNT; nGroup++) {
        pMember = func_020255d4(pReq->pArchive, nGroup, 0);
        nNodes = func_ov022_020b1078(pMember);
        pInfo = pReq->pInfo;
        for (nIndex = 0; nIndex < nNodes; nIndex++) {
            pNode = func_020170c8(pMember, nIndex);
            nTableSize = NTRi_GetRegionTableSize(pNode, pInfo->pRegion);
            pSet->apNodes[nGroup][nIndex] = pNext;
            if (nGroup == TEX_GROUP) {
                pTex = func_02017088(func_020255d4(pInfo->pOwner->pArchive, TEX_MEMBER, 0));
            } else {
                pTex = 0;
            }
            func_02014abc(pSet->apNodes[nGroup][nIndex], pNode, pInfo->pRegion, pTex);
            pNext += nTableSize;
            pReq->nUsed += nTableSize;
        }
        pSet->anCounts[nGroup] = nNodes;
    }
    pSet->nTag = pReq->nCount + TAG_BIAS;
}
