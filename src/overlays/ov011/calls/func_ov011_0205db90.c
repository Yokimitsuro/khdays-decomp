/* func_ov011_0205db90 -- unpack the scene's variable-length record file into a table.
 *
 * The file is a count followed by that many 4-byte descriptors, with all the payloads
 * packed end to end behind them. This walks the descriptors, copies the two leading
 * bytes into an 8-byte table entry and fills in a pointer to where that record's payload
 * starts -- NULL when the record is empty -- advancing a cursor by the record's length in
 * halfwords. Both the file and the table are parked on the scene.
 *
 * Three ordering facts, each worth one instruction:
 *   - the ternary is `length == 0 ? NULL : cursor`, not the negated form; mwcc emits the
 *     arms in source order, so `!=` swaps the moveq/movne pair;
 *   - the loop is a while, and `i = 0` comes BEFORE the cursor is computed -- as a for-init
 *     the counter is zeroed after it and the two setup instructions swap;
 *   - the count is copied into the table before either, which is what puts the file's
 *     count load where the ROM has it. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov011PackedEntry {
    u8  nA;
    u8  nB;
    u16 nLength;
} Ov011PackedEntry;

typedef struct Ov011PackedFile {
    u32              nCount;
    Ov011PackedEntry aEntries[1];
} Ov011PackedFile;

typedef struct Ov011Entry {
    u8         nA;
    u8         nB;
    u16        pad_02;
    const u16 *pData;
} Ov011Entry;

typedef struct Ov011Table {
    u32        nCount;
    Ov011Entry aEntries[1];
} Ov011Table;

typedef struct Ov011Scene {
    u8               pad_00000[0x2cf44];
    Ov011Table      *pTable;
    Ov011PackedFile *pFile;
} Ov011Scene;

typedef struct Ov011Globals {
    int         nCursor;
    Ov011Scene *pScene;
} Ov011Globals;

extern Ov011Globals data_ov011_0205e960;
extern u32 data_ov011_0205e938[];

extern void *func_0201ef9c(u32 nHandle, int nHeap);
extern void *NNSi_FndAllocFromDefaultExpHeap(u32 nSize);

void func_ov011_0205db90(void)
{
    Ov011PackedFile *pFile = func_0201ef9c((u32)data_ov011_0205e938, 0xe);
    Ov011Table *pTable = NNSi_FndAllocFromDefaultExpHeap(pFile->nCount * 8 + 4);
    const u16 *pCursor;
    u32 i;

    pTable->nCount = pFile->nCount;
    i = 0;
    pCursor = (const u16 *)&pFile->aEntries[pFile->nCount];
    while (i < pFile->nCount) {
        pTable->aEntries[i].nA = pFile->aEntries[i].nA;
        pTable->aEntries[i].nB = pFile->aEntries[i].nB;
        pTable->aEntries[i].pData = pFile->aEntries[i].nLength == 0 ? 0 : pCursor;
        pCursor += pFile->aEntries[i].nLength;
        i++;
    }
    data_ov011_0205e960.pScene->pFile = pFile;
    data_ov011_0205e960.pScene->pTable = pTable;
}
