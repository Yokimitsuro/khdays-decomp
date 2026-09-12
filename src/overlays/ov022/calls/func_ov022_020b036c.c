/* Ov022_LoadActionVoices -- load the voice files the action table's entries
 * name and bind them to the voice animation.
 *
 * Every entry with bit 0 of its flags contributes its tag once to a set of
 * up to sixteen. With any tags at all the voice animation is registered
 * from the actor's container (the file after the anim kind plus 0x28), the
 * voice flag is raised and the bind, tag and file arrays sized to the set.
 * Actor kind 0xd with anim kinds 0x11 or 0x12, and kind 10 with anim kinds
 * 0xf..0x12 or 0x15, take their voices from their own container instead of
 * the actor's, from index 0 rather than 0x8c. Each tag then names a file
 * -- kind 4 and kind 6 remap tags 6 and 8 by anim kind -- loaded into the
 * slot after the actor's own, bound to the voice animation and recorded.
 * A container opened here goes back.
 */

typedef unsigned char u8;
typedef unsigned int u32;

#define TAG_MAX 16
#define TAG_NONE (-1)
#define ENTRY_FLAG_VOICE 0x1
#define FLAG_VOICES 0x1
#define CONTAINER_HEAP 6
#define FILE_INDEX_MASK 0x1ff
#define VOICE_FILE_BASE 0x8c
#define ANIM_FILE_BASE 0x28
#define VOICE_BIND_SIZE 0x24

/* Ov022Ent */
struct Entry {
    u8 pad0000[3];
    u8 nTag;                     /* 0x03 */
    u8 pad0004[0x28];
    u32 nFlags2c;                /* 0x2c */
    u8 pad0030[0x50];
};

/* Ov022VoiceSet */
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
    u8 nSlotBase;                /* 0x0004 */
    u8 pad0005[3];
    u8 blkMove;                  /* 0x0008, its first byte the anim kind */
    u8 pad0009[0x7f];
    struct Entry *pEntries;      /* 0x0088 */
    int nEntryCount;             /* 0x008c */
    struct VoiceSet voice;       /* 0x0090 */
};

struct Actor {
    u8 pad0000[0xc];
    int nKind;                   /* 0x000c */
    u8 pad0010[0x2bc0];
    void *pContainer;            /* 0x2bd0 */
};

extern char data_ov022_020b2d70[];
extern char data_ov022_020b2d80[];

extern void func_0202a634(struct VoiceSet *pVoice, u32 nFile, int nArg, int nSlot);   /* RegisterSeqAndInit */
extern void *NNSi_FndAllocFromDefaultExpHeap(u32 nSize);
extern void *func_02024ee8(char *pszName, int nHeap);                           /* Msg_OpenContainerAndReadHeader */
extern void *func_0201ef9c(u32 nFile, int nSlot);                               /* Archive_LoadFile */
extern void func_0202a3cc(u8 *pBind, struct VoiceSet *pVoice, void *pFile, int nSlot);   /* Resource_BindFileToSlot */
extern void func_02024fd4(void *pContainer);                                    /* ZeroHalfThenFree */

void func_ov022_020b036c(struct ActionTable *pTable, struct Actor *pActor)
{
    u32 aTags[TAG_MAX];
    struct VoiceSet *pVoice;
    u8 *pMove;
    struct Entry *pEntry;
    int bNew;
    int nBase;
    void *pContainer;
    int bOwnContainer;
    int nTag;
    int i;
    int n;
    u32 nMask;

    pMove = &pTable->blkMove;
    pVoice = &pTable->voice;
    for (i = 0; i < TAG_MAX; i++) {
        aTags[i] = TAG_NONE;
    }
    pVoice->nCount = 0;
    for (i = 0; i < pTable->nEntryCount; i++) {
        pEntry = &pTable->pEntries[i];
        if ((pEntry->nFlags2c & ENTRY_FLAG_VOICE) != 0) {
            bNew = 1;
            for (n = 0; n < pVoice->nCount; n++) {
                if (pEntry->nTag == aTags[n]) {
                    bNew = 0;
                    break;
                }
            }
            if (bNew) {
                aTags[pVoice->nCount] = pEntry->nTag;
                pVoice->nCount++;
            }
        }
    }
    if (pVoice->nCount != 0) {
        nMask = 0xfffffc;
        func_0202a634(pVoice, ((((u32)pActor->pContainer + 0x8000) & nMask) << 7) | 0x80000000
                      | ((*pMove + ANIM_FILE_BASE) & (nMask >> 15)), 1, pTable->nSlotBase);
        pTable->nFlags |= FLAG_VOICES;
        nBase = VOICE_FILE_BASE;
        pContainer = pActor->pContainer;
        bOwnContainer = 0;
        pVoice->pBinds = NNSi_FndAllocFromDefaultExpHeap(pVoice->nCount * VOICE_BIND_SIZE);
        pVoice->pTags = NNSi_FndAllocFromDefaultExpHeap(pVoice->nCount);
        pVoice->ppFiles = NNSi_FndAllocFromDefaultExpHeap(pVoice->nCount * sizeof(void *));
        if (pActor->nKind == 0xd && (*pMove == 0x11 || *pMove == 0x12)) {
            bOwnContainer = 1;
            nBase = 0;
            pContainer = func_02024ee8(data_ov022_020b2d70, CONTAINER_HEAP);
        }
        if (pActor->nKind == 10) {
            switch (*pMove) {
            case 0xf:
            case 0x10:
            case 0x11:
            case 0x12:
            case 0x15:
                bOwnContainer = 1;
                nBase = 0;
                pContainer = func_02024ee8(data_ov022_020b2d80, CONTAINER_HEAP);
                break;
            }
        }
        for (i = 0; i < pVoice->nCount; i++) {
            nTag = aTags[i];
            if (pActor->nKind == 4) {
                if ((*pMove == 0x10 || *pMove == 0x11) && nTag == 8) {
                    nTag = 0xc;
                } else if ((*pMove == 0x12 || *pMove == 0x13) && nTag == 8) {
                    nTag = 0xd;
                }
            }
            if (pActor->nKind == 6) {
                switch (*pMove) {
                case 2:
                    if (nTag == 8) {
                        nTag = 0xa;
                    }
                    break;
                case 4:
                    if (nTag == 8) {
                        nTag = 0xb;
                    }
                    break;
                case 5:
                    if (nTag == 6) {
                        nTag = 0xc;
                    } else if (nTag == 8) {
                        nTag = 0xd;
                    }
                    break;
                case 6:
                    if (nTag == 6) {
                        nTag = 0xe;
                    } else if (nTag == 8) {
                        nTag = 0xf;
                    }
                    break;
                case 0x13:
                    if (nTag == 8) {
                        nTag = 0x10;
                    }
                    break;
                case 0x15:
                    if (nTag == 6) {
                        nTag = 0x11;
                    } else if (nTag == 8) {
                        nTag = 0x12;
                    }
                    break;
                }
            }
            pVoice->ppFiles[i] = func_0201ef9c(((((u32)pContainer + 0x8000) & nMask) << 7) | 0x80000000
                                               | ((nBase + nTag) & FILE_INDEX_MASK), pTable->nSlotBase + 7);
            func_0202a3cc(pVoice->pBinds + i * VOICE_BIND_SIZE, pVoice, pVoice->ppFiles[i], pTable->nSlotBase + 7);
            pVoice->pTags[i] = aTags[i];
        }
        if (bOwnContainer) {
            func_02024fd4(pContainer);
        }
    }
}
