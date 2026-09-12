/* Ov022_InitSyncSession -- set up the sync session in the root context and
 * hand back its reset step.
 *
 * The root context becomes the session: its seen-bitmap recorder is
 * registered under handler 8, its four buffer slots are cleared, and every
 * request of the four banks of three is reset (row, column, no phase, no
 * info, no archive) along with the seen byte. Then one, two or four
 * 0x9000-byte buffers are taken from the default heap and cleared -- four
 * when the player count passes one, two when the mode byte is 0x2a, one
 * otherwise -- and the four slots' video memory is split in mode 2. The
 * caller keeps the bank reset step.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* Ov022SyncRequest */
struct SyncRequest {
    u8 nFlags;                   /* 0x00 */
    u8 nRow;                     /* 0x01 */
    u8 nCol;                     /* 0x02 */
    u8 nPhase;                   /* 0x03 */
    u8 nodeSet[0x24];            /* 0x04 */
    void *pInfo;                 /* 0x28 */
    void *pArchive;              /* 0x2c */
    u16 nSize;                   /* 0x30 */
    u8 pad32[2];
    u16 nUsed;                   /* 0x34 */
    u16 nMsgId;                  /* 0x36 */
};

/* Ov022SyncSession */
struct SyncSession {
    void *apBuffers[4];          /* 0x000 */
    struct SyncRequest aRequests[4][3];   /* 0x010 */
    u8 aSeen[8][3];              /* 0x2b0 */
};

typedef int (*ResetFn)(void);

#define BANK_COUNT 4
#define BANK_SIZE 3
#define HANDLER_SEEN 8
#define BUFFER_SIZE 0x9000
#define MODE_TWO_BUFFERS 0x2a
#define SLOT_COUNT 4
#define SPLIT_MODE 2

extern struct SyncSession *data_ov022_020b2eb8;      /* gpOv022SyncSession */

extern struct SyncSession *NNSi_FndGetCurrentRootHeap(void);
extern void func_02030cf8(int nHandler, void (*pfn)(u8 *pId));
extern void func_ov022_020b0e64(u8 *pId);                                      /* Ov022_RecordSeenSlot */
extern int func_ov022_020882f8(void);
extern int func_02020a9c(void);
extern void *NNSi_FndAllocFromDefaultExpHeap(u32 nSize);
extern void MIi_CpuClearFast(u32 nValue, void *pDst, u32 nSize);
extern void func_ov022_020b15b0(int nId, int nMode);                            /* Ov022_SplitSlotVram */
extern int func_ov022_020b102c(void);                                           /* Ov022_ResetSyncBanks */

ResetFn func_ov022_020b0f2c(void)
{
    struct SyncSession *pSession;
    struct SyncRequest *pRow;
    int i;
    int j;
    int k;
    int nCount;

    pSession = NNSi_FndGetCurrentRootHeap();
    data_ov022_020b2eb8 = pSession;
    func_02030cf8(HANDLER_SEEN, func_ov022_020b0e64);
    for (i = 0; i < BANK_COUNT; i++) {
        pSession->apBuffers[i] = 0;
        pRow = pSession->aRequests[i];
        for (j = 0; j < BANK_SIZE; j++) {
            pRow[j].pArchive = 0;
            pRow[j].nCol = j;
            pRow[j].nRow = i;
            pRow[j].nPhase = 0;
            pRow[j].pInfo = 0;
            pSession->aSeen[i][j] = 0;
        }
    }
    if (func_ov022_020882f8() > 1) {
        nCount = 4;
    } else if (func_02020a9c() == MODE_TWO_BUFFERS) {
        nCount = 2;
    } else {
        nCount = 1;
    }
    for (k = 0; k < nCount; k++) {
        pSession->apBuffers[k] = NNSi_FndAllocFromDefaultExpHeap(BUFFER_SIZE);
        MIi_CpuClearFast(0, pSession->apBuffers[k], BUFFER_SIZE);
    }
    for (i = 0; i < SLOT_COUNT; i++) {
        func_ov022_020b15b0(i, SPLIT_MODE);
    }
    return func_ov022_020b102c;
}
