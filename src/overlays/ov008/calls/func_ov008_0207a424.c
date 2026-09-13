/* func_ov008_0207a424 -- Ov008_MissionLobbyStartTransfer: start the mission
 * lobby's transfer; returns the poll handler (0207a758, after setting
 * +0x4fc and field 28 of the global block to 2) once a transfer started, or
 * 0.  While the transfer is busy (+0x4e8), or with the session ready, the
 * group message (+0x4a8: header word + four join packets) is built once
 * (+0x4f8): cleared, every occupied slot's member kind resolved to the
 * packet's target, every packet marked pending and joined by the bit of the
 * lobby mask (01fff974); the message is then copied to +0x4c4 and, with the
 * session, sent on gate 0xd.  Otherwise, with the list header (+0x4a0) at 1,
 * the local player's packet becomes the join packet (+0x4e0) and the header
 * is cleared without a transfer; else the header is cleared, the join packet
 * is marked pending while no retry (+0x4f2) happened, given the local player
 * with no target and sent on gate 0xd.  Codegen: the message build is a
 * static inline helper (two copies) taking the packets through a local
 * pointer; the u8 loop counter walks a byte index.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define GATE_LOBBY   0xd
#define SLOT_COUNT   4

typedef struct Ov008JoinPacket {
    u8  nPlayer;              /* 0x00 */
    u8  bJoined : 1;          /* 0x01 bit 0 */
    u8  bPending : 1;         /*      bit 1 */
    u8  nSpare : 6;
    signed char nTarget;      /* 0x02 */
    u8  nPad;                 /* 0x03 */
    u16 nArg;                 /* 0x04 */
} Ov008JoinPacket;

typedef struct Ov008GroupMessage {
    u32 nHeader;              /* 0x00 */
    Ov008JoinPacket aPacket[SLOT_COUNT]; /* 0x04 */
} Ov008GroupMessage;

typedef struct SessionSlotInfo {
    int bOccupied;            /* 0x00 */
    int nMemberKind;          /* 0x04 */
} SessionSlotInfo;

typedef struct MissionContext {
    u8  pad_0000[0x4a0];
    int nListHeader;          /* 0x4a0 */
    u8  pad_04a4[4];
    Ov008GroupMessage group;  /* 0x4a8 */
    Ov008GroupMessage groupSent; /* 0x4c4 */
    Ov008JoinPacket join;     /* 0x4e0 */
    u8  pad_04e6[2];
    int nTransferBusy;        /* 0x4e8 */
    u8  pad_04ec[6];
    u16 nRetryCount;          /* 0x4f2 */
    u8  pad_04f4[4];
    int bGroupBuilt;          /* 0x4f8 */
    int nTransferB;           /* 0x4fc */
} MissionContext;

extern MissionContext *data_ov008_02090f24;
extern u16   func_01fff974(void);                                 /* lobby slot mask */
extern void  MI_CpuFill8(void *pDst, int nValue, u32 nSize);
extern SessionSlotInfo *func_020315c0(int nSlot);                 /* Slot4_GetIfOccupied */
extern int   func_ov008_0207937c(int nMemberKind);                /* member kind -> packet target */
extern int   func_02030694(void);                                 /* Session_IsReady */
extern void  func_02031258(int nGate, void *pBuf, int nSize);     /* MsgQueue_SendGate */
extern u32   func_02030788(void);                                 /* Session_GetLocalPlayerIndex */
extern void  func_02023c14(int nValue);                           /* StoreToGlobalPtr4Field28 */
extern void *func_ov008_0207a758(void);                           /* Ov008_MissionLobbyPoll */

static inline void Ov008_BuildGroupMessage(MissionContext *pCtx)
{
    Ov008JoinPacket *pPacket;
    u16 nMask;
    u8 i;
    SessionSlotInfo *pInfo;

    pPacket = pCtx->group.aPacket;
    nMask = func_01fff974();
    if (data_ov008_02090f24->bGroupBuilt == 0) {
        MI_CpuFill8(&data_ov008_02090f24->group, 0, sizeof(Ov008GroupMessage));
        for (i = 0; i < SLOT_COUNT; i++) {
            pInfo = func_020315c0(i);
            if (pInfo != 0) {
                pPacket[i].nTarget = func_ov008_0207937c(pInfo->nMemberKind);
            }
            pPacket[i].bPending = 1;
            pPacket[i].bJoined = (nMask & (1 << i)) != 0;
        }
        data_ov008_02090f24->bGroupBuilt = 1;
    }
}

void *func_ov008_0207a424(void)
{
    int bStarted;
    void *pNext;
    MissionContext *pCtx;
    u16 nPlayer;

    bStarted = 0;
    pNext = 0;
    pCtx = data_ov008_02090f24;
    if (pCtx->nTransferBusy != 0) {
        Ov008_BuildGroupMessage(pCtx);
        bStarted = 1;
        pCtx = data_ov008_02090f24;
        pCtx->groupSent = pCtx->group;
    } else if (func_02030694() != 0) {
        pCtx = data_ov008_02090f24;
        Ov008_BuildGroupMessage(pCtx);
        pCtx = data_ov008_02090f24;
        pCtx->groupSent = pCtx->group;
        func_02031258(GATE_LOBBY, &pCtx->group, sizeof(Ov008GroupMessage));
        bStarted = 1;
    } else if (data_ov008_02090f24->nListHeader == 1) {
        nPlayer = func_02030788();
        pCtx = data_ov008_02090f24;
        pCtx->join = pCtx->group.aPacket[nPlayer];
        bStarted = 1;
        pCtx->join.nPlayer = nPlayer;
        data_ov008_02090f24->nListHeader = 0;
    } else {
        data_ov008_02090f24->nListHeader = 0;
        pCtx = data_ov008_02090f24;
        pCtx->join.bPending = pCtx->nRetryCount == 0;
        data_ov008_02090f24->join.nPlayer = func_02030788();
        data_ov008_02090f24->join.nTarget = -1;
        data_ov008_02090f24->join.nArg = 0;
        func_02031258(GATE_LOBBY, &data_ov008_02090f24->join, sizeof(Ov008JoinPacket));
    }
    if (bStarted != 0) {
        data_ov008_02090f24->nTransferB = 1;
        func_02023c14(2);
        pNext = func_ov008_0207a758;
    }
    return pNext;
}
