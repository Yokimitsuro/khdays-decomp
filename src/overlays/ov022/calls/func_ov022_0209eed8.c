/* Ov022_LoadCueTables -- load the actor's voice cue tables from its kind's
 * cue file.
 *
 * Every reaction's table slot and the two pools are cleared first. The
 * kind's cue file is read out of the container: a header of five counts
 * and offsets, then the tables, the entries and the voices. The voices
 * become a pool of (voice, argument) pairs; the entries a pool of timed
 * cues -- frame, the single flag bit, mode and count, with the done bit and
 * the voice handle cleared and each cue index turned into a pointer into
 * the voice pool. Each table then claims its reaction's slot with its count
 * of entry pointers. The file and container go back.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define TABLE_SLOTS 54
#define CONTAINER_HEAP 6
#define FILE_HEAP 6
#define HEADER_SIZE 0x14
#define ENTRY_HEAD_SIZE 0x10
#define TABLE_HEAD_SIZE 8

/* Ov022VoiceCue */
struct VoiceCue {
    u16 nVoice;                  /* 0x00 */
    u16 nArg;                    /* 0x02 */
};

/* Ov022CueEntry */
struct CueEntry {
    int nFrame;                  /* 0x00 */
    u8 bFlag0 : 1;               /* 0x04 bit 0 */
    u8 bDone : 1;                /* bit 1 */
    u8 nRest04 : 6;
    u8 nMode;                    /* 0x05 */
    u8 nCount;                   /* 0x06 */
    u8 pad07;
    int hVoice;                  /* 0x08 */
    struct VoiceCue *apCues[3];  /* 0x0c */
};

/* Ov022CueTable */
struct CueTable {
    u8 nReaction;                /* 0x00 */
    u8 nCount;                   /* 0x01 */
    u8 pad02[2];
    struct CueEntry **apEntries; /* 0x04 */
};

/* Ov022CueFile: the cue file's header */
struct CueFile {
    int nTableCount;             /* 0x00 */
    int nEntryCount;             /* 0x04 */
    int nEntryOffset;            /* 0x08 */
    int nVoiceCount;             /* 0x0c */
    int nVoiceOffset;            /* 0x10 */
};

/* Ov022Actor */
struct Actor {
    u8 pad0000[0xc];
    int nKind;                   /* 0x000c */
    u8 pad0010[0x6b0];
    struct CueTable *apCueTables[TABLE_SLOTS];   /* 0x06c0 */
    struct CueEntry *pCueEntries;                /* 0x0798 */
    struct VoiceCue *pCueVoices;                 /* 0x079c */
    int nCueEntryCount;          /* 0x07a0 */
};

extern char data_ov022_020b2d50[];

extern void *func_02024ee8(char *pszName, int nHeap);                           /* Msg_OpenContainerAndReadHeader */
extern struct CueFile *func_0201ef9c(u32 nFile, int nHeap);                     /* Archive_LoadFile */
extern void *NNSi_FndAllocFromDefaultExpHeap(u32 nSize);
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void func_02024fd4(void *pContainer);

void func_ov022_0209eed8(struct Actor *pActor)
{
    void *pContainer;
    struct CueFile *pFile;
    int nPos;
    int nTable;
    int i;
    struct CueEntry *pEntry;
    int j;
    int nOff;
    int *pSrc;
    u8 *pBytes;
    struct CueTable *pTable;
    u32 nMask;

    for (i = 0; i < TABLE_SLOTS; i++) {
        pActor->apCueTables[i] = 0;
    }
    pActor->pCueVoices = 0;
    pActor->pCueEntries = 0;
    pContainer = func_02024ee8(data_ov022_020b2d50, CONTAINER_HEAP);
    nMask = 0xfffffc;
    pFile = func_0201ef9c(((((u32)pContainer + 0x8000) & nMask) << 7) | 0x80000000
                          | (pActor->nKind & (nMask >> 15)), FILE_HEAP);
    pSrc = (int *)((u8 *)pFile + pFile->nVoiceOffset);
    pActor->pCueVoices = NNSi_FndAllocFromDefaultExpHeap(pFile->nVoiceCount * sizeof(struct VoiceCue));
    for (i = 0; i < pFile->nVoiceCount; i++) {
        pActor->pCueVoices[i].nVoice = pSrc[0];
        pActor->pCueVoices[i].nArg = pSrc[1];
        pSrc += 2;
    }
    pActor->pCueEntries = NNSi_FndAllocFromDefaultExpHeap(pFile->nEntryCount * sizeof(struct CueEntry));
    pActor->nCueEntryCount = pFile->nEntryCount;
    nOff = pFile->nEntryOffset;
    for (i = 0; i < pFile->nEntryCount; i++) {
        pBytes = (u8 *)pFile + nOff;
        pEntry = &pActor->pCueEntries[i];
        pActor->pCueEntries[i].nFrame = *(int *)((u8 *)pFile + nOff);
        nOff += ENTRY_HEAD_SIZE;
        pEntry->bFlag0 = (u8)*(int *)(pBytes + 4);
        pEntry->nMode = *(int *)(pBytes + 8);
        pEntry->nCount = *(int *)(pBytes + 0xc);
        pEntry->hVoice = 0;
        pEntry->bDone = 0;
        if ((int)pActor->pCueEntries[i].nCount > 0) {
            pBytes += 0x10;
            for (j = 0; j < pActor->pCueEntries[i].nCount; j++) {
                nOff += 4;
                pEntry->apCues[j] = &pActor->pCueVoices[*(int *)pBytes];
                pBytes += 4;
            }
        }
    }
    nPos = HEADER_SIZE;
    for (nTable = 0; nTable < pFile->nTableCount; nTable++) {
        pSrc = (int *)((u8 *)pFile + nPos);
        pActor->apCueTables[*(int *)((u8 *)pFile + nPos)] = NNSi_FndAllocFromDefaultExpHeap(sizeof(struct CueTable));
        pTable = pActor->apCueTables[*(int *)((u8 *)pFile + nPos)];
        pTable->nReaction = *(int *)((u8 *)pFile + nPos);
        pTable->nCount = pSrc[1];
        pTable->apEntries = NNSi_FndAllocFromDefaultExpHeap(pTable->nCount * sizeof(struct CueEntry *));
        j = 0;
        nPos += TABLE_HEAD_SIZE;
        if ((int)pTable->nCount > 0) {
            pSrc += 2;
            for (; j < pTable->nCount; j++) {
                pTable->apEntries[j] = &pActor->pCueEntries[*pSrc];
                pSrc++;
                nPos += 4;
            }
        }
    }
    NNSi_FndFreeFromDefaultHeap(pFile);
    func_02024fd4(pContainer);
}
