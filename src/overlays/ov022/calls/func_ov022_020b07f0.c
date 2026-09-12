/* Ov022_TearDownActionTable -- give back everything an action table owns.
 *
 * The rows are unbound and their files freed up to the first unused one,
 * each marked unused again. The entries of the entry table lose their data
 * and the table itself goes. Every list of the two groups goes. When the
 * voice pass ran (flag bit 0), the voice animation is released, each voice
 * bind is unbound and its file freed, and with any voices at all the file
 * list, the binds and the tags go too; the flag drops.
 */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;

#define ROW_COUNT 0x10
#define ROW_INDEX_NONE (-1)
#define GROUP_COUNT 2
#define LIST_COUNT 3
#define FLAG_VOICES 0x1

/* Ov022Actioi */
struct Row {
    s8 nIndex;                   /* 0x00 */
    u8 pad0001[3];
    u8 blkBind;                  /* 0x04 */
    u8 pad0005[0x23];
    void *pFile;                 /* 0x28 */
};

/* Ov022ActionGroup */
struct Group {
    u8 pad0000[0x18];
    void *apLists[LIST_COUNT];   /* 0x18 */
    u8 pad0024[0xc];
};

/* Ov022Ent */
struct Entry {
    u8 pad0000[0x34];
    void *pData;                 /* 0x34 */
    u8 pad0038[0x48];
};

/* Ov022VoiceSet: the voice pass block at 0x90 of the action table */
struct VoiceSet {
    u8 blkAnim[0x108];           /* 0x000 */
    u8 *pBinds;                  /* 0x108, 0x24 each */
    void **ppFiles;              /* 0x10c */
    int nCount;                  /* 0x110 */
    u8 *pTags;                   /* 0x114 */
};

/* Ov022ActionTable */
struct ActionTable {
    u32 nFlags;                  /* 0x0000 */
    u8 pad0004[0x24];
    struct Group aGroups[GROUP_COUNT];   /* 0x0028 */
    struct Entry *pEntries;      /* 0x0088 */
    int nEntryCount;             /* 0x008c */
    struct VoiceSet voice;       /* 0x0090 */
    struct Row aRows[ROW_COUNT]; /* 0x01a8 */
};

#define VOICE_BIND_SIZE 0x24

extern void func_0202a440(u8 *pBind);                                           /* FreeAllResourceTables */
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void func_0202a7dc(u8 *pAnim);                                           /* ReleaseField74AndCleanup */

void func_ov022_020b07f0(struct ActionTable *pTable)
{
    int i;
    struct Row *pRow;
    int nList;
    struct Group *pGroup;
    int nGroup;
    struct VoiceSet *pVoice;
    int nVoice;

    pRow = pTable->aRows;
    for (i = 0; i < ROW_COUNT; i++) {
        if (pRow->nIndex == ROW_INDEX_NONE) {
            break;
        }
        func_0202a440(&pRow->blkBind);
        NNSi_FndFreeFromDefaultHeap(pRow->pFile);
        pRow->nIndex = ROW_INDEX_NONE;
        pRow++;
    }
    for (i = 0; i < pTable->nEntryCount; i++) {
        NNSi_FndFreeFromDefaultHeap(pTable->pEntries[i].pData);
    }
    NNSi_FndFreeFromDefaultHeap(pTable->pEntries);
    pGroup = pTable->aGroups;
    for (nGroup = 0; nGroup < GROUP_COUNT; nGroup++) {
        for (nList = 0; nList < LIST_COUNT; nList++) {
            if (pGroup->apLists[nList] != 0) {
                NNSi_FndFreeFromDefaultHeap(pGroup->apLists[nList]);
            }
        }
        pGroup++;
    }
    if ((pTable->nFlags & FLAG_VOICES) != 0) {
        pVoice = &pTable->voice;
        func_0202a7dc(pVoice->blkAnim);
        for (nVoice = 0; nVoice < pVoice->nCount; nVoice++) {
            func_0202a440(pVoice->pBinds + nVoice * VOICE_BIND_SIZE);
            NNSi_FndFreeFromDefaultHeap(pVoice->ppFiles[nVoice]);
        }
        if (pVoice->nCount > 0) {
            NNSi_FndFreeFromDefaultHeap(pVoice->ppFiles);
            NNSi_FndFreeFromDefaultHeap(pVoice->pBinds);
            NNSi_FndFreeFromDefaultHeap(pVoice->pTags);
        }
        pTable->nFlags &= ~FLAG_VOICES;
    }
}
