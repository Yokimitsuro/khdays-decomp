/* ov022: load the files the action table's rows name.
 *
 * The table's rows were left with an index of -1 by the builder, so the walk
 * stops at the first one that still is. Every other row names a file inside the
 * container the kind opens, addressed by the packed spec built from the
 * container's own address, and the file is bound to the actor's animation as
 * that row's own resource. The container goes back once the rows are done.
 */

#include "nitro/types.h"

#define ROW_COUNT 0x10
#define CONTAINER_HEAP 6
#define ROW_INDEX_NONE (-1)
#define FILE_INDEX_MASK 0x1ff

struct Row {
    s8 nIndex;                   /* 0x00, -1 once the rows run out */
    u8 pad0001[3];
    u8 blkBind;                  /* 0x04 */
    u8 pad0005[0x23];
    void *pFile;                 /* 0x28 */
};

struct ActionTable {
    u8 pad0000[4];
    u8 nSlotBase;                /* 0x04 */
    u8 pad0005[0x1a3];
    struct Row aRows[ROW_COUNT]; /* 0x1a8 */
};

struct Actor {
    u8 pad0000[0x20];
    u8 *pAnim;                   /* 0x20 */
};

extern char *data_02042a70[];
extern char gOv022AmPathFmt[];
extern char gOv022BaChPath[];

extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void *Msg_OpenContainerAndReadHeader(char *pszName, int nHeap);
extern void *Archive_LoadFile(u32 nFile, int nSlot);
extern void Resource_BindFileToSlot(u8 *pBind, u8 *pAnim, void *pFile, int nSlot);
extern void ZeroHalfThenFree(void *pContainer);

void Ov022_LoadActionRows(struct ActionTable *pTable, struct Actor *pActor,
                         int nKind)
{
    char szName[0x80];
    void *pContainer;
    struct Row *pRow;
    u32 nMask;
    u32 nBase;
    int nRow;

    OS_SPrintf(szName, gOv022AmPathFmt, gOv022BaChPath,
               data_02042a70[nKind]);
    pContainer = Msg_OpenContainerAndReadHeader(szName, CONTAINER_HEAP);
    pRow = pTable->aRows;
    nMask = 0xfffffc;
    nBase = ((((u32)pContainer + 0x8000) & nMask) << 7) | 0x80000000;
    for (nRow = 0; nRow < ROW_COUNT; nRow++) {
        if (pRow->nIndex == ROW_INDEX_NONE) {
            break;
        }
        pRow->pFile = Archive_LoadFile(nBase | (pRow->nIndex & FILE_INDEX_MASK),
                                    pTable->nSlotBase + 7);
        Resource_BindFileToSlot(&pRow->blkBind, pActor->pAnim + 4, pRow->pFile,
                      pTable->nSlotBase + 7);
        pRow++;
    }
    ZeroHalfThenFree(pContainer);
}
