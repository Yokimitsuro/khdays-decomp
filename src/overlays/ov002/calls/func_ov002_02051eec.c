/* Load an actor's animation tables from the archive.
 *
 * Counts the ids the state block carries, at most thirteen and terminated by
 * -1, allocates one table per id and fills them in order. Each archive path is
 * packed from the group and the file id; since 0x1ff is 0xfffffc shifted right
 * by fifteen, mwcc shares one pool word for both masks. The loaded blocks are
 * kept so the teardown can free them, and the count lands last, which is what
 * makes a partially built block look empty.
 */
typedef struct Ov002AnimStateBlock {
    char nCurrentMode;
    char pad0001[3];
    int bModeChanged;
    char anAnimIds[13];     /* +8, terminated by -1 */
    char pad0015[3];
    void *apBlocks[13];     /* +0x18 */
    char *pTables;          /* +0x4c, stride 0x24 */
    int nTableCount;        /* +0x50 */
} Ov002AnimStateBlock;

extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned long size);

/* Three arguments, not four: the ROM reaches the call with r3 never written. */
extern void *func_0201ef9c(char *pPath, int nHeap, int nFileId);

extern void func_0202a3cc(void *pTable, void *pAnim, void *pData, int nHeap);

void func_ov002_02051eec(char *pActor, char *pAnimState, int nGroup, int nHeap,
                         int nBaseId) {
    Ov002AnimStateBlock *pState = (Ov002AnimStateBlock *)pAnimState;
    int nCount;
    int i;
    int nOffset;

    nCount = 0;
    i = 0;
    do {
        if (pState->anAnimIds[i] == -1) {
            break;
        }
        i++;
        nCount++;
    } while (i < 0xd);

    if (nCount <= 0) {
        return;
    }
    pState->pTables = (char *)NNSi_FndAllocFromDefaultExpHeap(nCount * 0x24);

    i = 0;
    if (0 < nCount) {
        int nDir = ((nGroup + 0x8000) & 0xfffffc) << 7;

        nOffset = 0;
        do {
            int nFileId = nBaseId + pState->anAnimIds[i];
            void *pData = func_0201ef9c(
                (char *)(nDir | 0x80000000 | (nFileId & 0x1ff)), nHeap + 7,
                nFileId);

            pState->apBlocks[i] = pData;
            func_0202a3cc(pState->pTables + nOffset, pActor + 4,
                          pState->apBlocks[i], nHeap + 7);
            i++;
            nOffset += 0x24;
        } while (i < nCount);
    }
    pState->nTableCount = nCount;
}
