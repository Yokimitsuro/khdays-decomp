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

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;

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
extern char data_ov022_020b2d68[];
extern char data_ov022_020b2d90[];
extern char data_ov022_020b2da0[];

extern void func_ov002_020522c8(u8 *pBlk, int nKind, int nArg);
extern int func_020358f4(int nId, int nWhat);
extern void OS_SPrintf(char *pszOut, char *pszFormat, char *pszSet,
                       char *pszKind);
extern void *func_0201ef9c(char *pszName, int nHeap);
extern void func_ov022_020afe14(struct ActionTable *pTable,
                                void *pFile);   /* rebase the anim records */
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void func_ov022_020aff84(struct ActionTable *pTable,
                                void *pFile);   /* link the anims */
extern void func_ov022_020b02d8(struct ActionTable *pTable,
                                struct Actor *pActor, int nKind);
extern void func_ov022_020b036c(struct ActionTable *pTable,
                                struct Actor *pActor,
                                int nArg);      /* load the voices */

void func_ov022_020b0720(struct ActionTable *pTable, struct Actor *pActor,
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
    func_ov002_020522c8(&pTable->blkMove, nKind, nArg);
    if (func_020358f4(pActor->nId, REACH_QUERY) != 0) {
        pTable->nAngle = pTable->nAngleAlt;
    }
    OS_SPrintf(szTableName, data_ov022_020b2d90, data_ov022_020b2d68,
               data_02042a70[nKind]);
    pFile = func_0201ef9c(szTableName, ARCHIVE_HEAP);
    func_ov022_020afe14(pTable, pFile);
    NNSi_FndFreeFromDefaultHeap(pFile);
    OS_SPrintf(szExtraName, data_ov022_020b2da0, data_ov022_020b2d68,
               data_02042a70[nKind]);
    pFile = func_0201ef9c(szExtraName, ARCHIVE_HEAP);
    func_ov022_020aff84(pTable, pFile);
    NNSi_FndFreeFromDefaultHeap(pFile);
    func_ov022_020b02d8(pTable, pActor, nKind);
    if (nKind != 2 && nKind != 9) {
        func_ov022_020b036c(pTable, pActor, nArg);
    }
}
