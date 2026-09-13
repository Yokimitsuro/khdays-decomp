/* func_ov008_0207a758 -- Ov008_MissionLobbyPoll: one poll of the mission
 * lobby's transfer state; returns the next state handler (0207aa40 once a
 * transfer (+0x4f4) is pending, after which field 28 of the global block is
 * set to 3) or 0.  While the transfer is busy (+0x4e8) only the pending
 * transfer is forwarded; otherwise, with the session ready, the transfer is
 * forwarded, the lobby refreshed (02079ae4) and the group header (+0x4a8,
 * 0x1c bytes) sent on gate 0xd, and without a session the join packet
 * (+0x4e0, 6 bytes) is sent instead.  Forwarding a transfer clears the four
 * slot infos (02031618) and then re-registers every joined packet (+0x4ac,
 * 6 each, bit 0 of +0x1) as kind 1 with its menu entry's slot.  Codegen: the
 * forwarding block is a static inline helper (three copies, each with its own
 * stack info); the packet array is taken through a local pointer.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define GATE_LOBBY   0xd
#define SLOT_COUNT   4
#define INFO_KIND_JOINED 1

typedef struct Ov008JoinPacket {
    u8  nPlayer;              /* 0x00 */
    u8  bJoined : 1;          /* 0x01 bit 0 */
    u8  bPending : 1;         /*      bit 1 */
    u8  nSpare : 6;
    signed char nTarget;      /* 0x02 */
    u8  nPad;                 /* 0x03 */
    u16 nArg;                 /* 0x04 */
} Ov008JoinPacket;

typedef struct Ov008SlotInfo {
    u32 nKind;                /* 0x00 */
    int nSlot;                /* 0x04 */
} Ov008SlotInfo;

typedef struct MissionContext {
    u8  pad_0000[0x4a8];
    u32 nGroupHeader;         /* 0x4a8 */
    Ov008JoinPacket aPacket[SLOT_COUNT]; /* 0x4ac */
    u8  pad_04c4[0x4e0 - 0x4c4];
    Ov008JoinPacket join;     /* 0x4e0 */
    u8  pad_04e6[2];
    int nTransferBusy;        /* 0x4e8 */
    u8  pad_04ec[8];
    int nTransferA;           /* 0x4f4 */
} MissionContext;

extern MissionContext *data_ov008_02090f24;
extern void  MI_CpuFill8(void *pDst, int nValue, u32 nSize);
extern void  func_02031618(Ov008SlotInfo *pInfo, int nSlot);      /* register a slot info */
extern int   func_ov008_0207928c(int nEntry);                     /* Ov008_MenuEntryToSlot */
extern u32   func_02030788(void);                                 /* Session_GetLocalPlayerIndex */
extern int   func_02030694(void);                                 /* Session_IsReady */
extern void  func_ov008_02079ae4(void);                           /* lobby refresh */
extern void  func_02031258(int nGate, void *pBuf, int nSize);     /* MsgQueue_SendGate */
extern void  func_02023c14(int nValue);                           /* StoreToGlobalPtr4Field28 */
extern void *func_ov008_0207aa40(void);                           /* next lobby state */

static inline void Ov008_ForwardJoinedSlots(MissionContext *pCtx)
{
    Ov008SlotInfo info;
    u8 i;
    u8 nSlot;
    Ov008JoinPacket *pPacket;

    pPacket = pCtx->aPacket;
    MI_CpuFill8(&info, 0, sizeof(info));
    for (i = 0; i < SLOT_COUNT; i++) {
        func_02031618(&info, i);
    }
    nSlot = 0;
    for (i = 0; i < SLOT_COUNT; i++) {
        MI_CpuFill8(&info, 0, sizeof(info));
        if (pPacket[i].bJoined) {
            info.nKind = INFO_KIND_JOINED;
            info.nSlot = func_ov008_0207928c(pPacket[i].nTarget);
            func_02031618(&info, nSlot);
            nSlot++;
        }
    }
}

void *func_ov008_0207a758(void)
{
    void *pNext;
    MissionContext *pCtx;

    pNext = 0;
    pCtx = data_ov008_02090f24;
    if (pCtx->nTransferBusy != 0) {
        if (pCtx->nTransferA != 0) {
            Ov008_ForwardJoinedSlots(pCtx);
            pNext = func_ov008_0207aa40;
        }
    } else {
        func_02030788();
        if (func_02030694() != 0) {
            pCtx = data_ov008_02090f24;
            if (pCtx->nTransferA != 0) {
                Ov008_ForwardJoinedSlots(pCtx);
                pNext = func_ov008_0207aa40;
            }
            func_ov008_02079ae4();
            func_02031258(GATE_LOBBY, &data_ov008_02090f24->nGroupHeader, 0x1c);
        } else {
            pCtx = data_ov008_02090f24;
            if (pCtx->nTransferA != 0) {
                Ov008_ForwardJoinedSlots(pCtx);
                pNext = func_ov008_0207aa40;
            }
            func_02031258(GATE_LOBBY, &data_ov008_02090f24->join, sizeof(Ov008JoinPacket));
        }
    }
    if (pNext == func_ov008_0207aa40) {
        func_02023c14(3);
    }
    return pNext;
}
