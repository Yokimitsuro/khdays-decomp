/* ov022: build the actor's action table.
 *
 * Clears the table, stamps the actor's slot base and marks every row empty, so
 * the row loader that follows knows where to stop. The move block is set up by
 * ov002, and an actor whose slot answers the reach query starts from the
 * second angle instead of the first. Two archives are then read into the table
 * in turn -- the animation records and the animation links -- each freed as
 * soon as it is folded in, and the rows' own files are loaded last. Two kinds
 * skip the trailing voice pass entirely.
 */

#include "nitro/types.h"

#define ROW_COUNT 0x10
#define ROW_INDEX_NONE (-1)
#define ARCHIVE_HEAP 6
#define REACH_QUERY 0x59

struct Row {
    s8 nIndex;                   /* 0x00 */
    u8 pad0001[0x2b];
};

struct ActionTable {
    u32 nFlags;                  /* 0x0000 */
    u8 nSlotBase;                /* 0x0004 */
    u8 pad0005[3];
    u8 blkMove;                  /* 0x0008 */
    u8 pad0009;
    short nAngle;                /* 0x000a */
    u8 pad000c[0xa];
    short nAngleAlt;             /* 0x0016 */
    u8 pad0018[0x190];
    struct Row aRows[ROW_COUNT]; /* 0x01a8 */
    u8 pad0468[0x10];
    u32 nField0478;              /* 0x0478 */
};

struct Actor {
    u8 pad0000[9];
    u8 nId;                      /* 0x0009 */
};

extern char *data_02042a70[];
extern char gOv022BaChPath[];
extern char gOv022CiPathFmt[];
extern char gOv022CmPathFmt[];

extern void Ov002_LoadCharacterWeapon(u8 *pBlk, int nKind, int nArg);
extern int Slot_EvalPackedParam(int nId, int nWhat);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void *Archive_LoadFile(char *pszName, int nHeap);
extern void Ov022_RebaseAnimRecord(struct ActionTable *pTable,
                                void *pFile);   /* rebase the anim records */
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void Ov022_LinkActionAnims(struct ActionTable *pTable,
                                void *pFile);   /* link the anims */
extern void Ov022_LoadActionRows(struct ActionTable *pTable,
                                struct Actor *pActor, int nKind);
extern void Ov022_LoadActionVoices(struct ActionTable *pTable,
                                struct Actor *pActor,
                                int nArg);      /* load the voices */

void Ov022_BuildActionTable(struct ActionTable *pTable, struct Actor *pActor,
                         int nKind, int nArg)
{
    char szTableName[0x81];
    char szExtraName[0x7f];
    void *pFile;
    int nRow;

    pTable->nFlags = 0;
    pTable->nField0478 = 0;
    pTable->nSlotBase = pActor->nId;
    for (nRow = 0; nRow < ROW_COUNT; nRow++) {
        pTable->aRows[nRow].nIndex = ROW_INDEX_NONE;
    }
    Ov002_LoadCharacterWeapon(&pTable->blkMove, nKind, nArg);
    if (Slot_EvalPackedParam(pActor->nId, REACH_QUERY) != 0) {
        pTable->nAngle = pTable->nAngleAlt;
    }
    OS_SPrintf(szTableName, gOv022CiPathFmt, gOv022BaChPath,
               data_02042a70[nKind]);
    pFile = Archive_LoadFile(szTableName, ARCHIVE_HEAP);
    Ov022_RebaseAnimRecord(pTable, pFile);
    NNSi_FndFreeFromDefaultHeap(pFile);
    OS_SPrintf(szExtraName, gOv022CmPathFmt, gOv022BaChPath,
               data_02042a70[nKind]);
    pFile = Archive_LoadFile(szExtraName, ARCHIVE_HEAP);
    Ov022_LinkActionAnims(pTable, pFile);
    NNSi_FndFreeFromDefaultHeap(pFile);
    Ov022_LoadActionRows(pTable, pActor, nKind);
    if (nKind != 2 && nKind != 9) {
        Ov022_LoadActionVoices(pTable, pActor, nArg);
    }
}
