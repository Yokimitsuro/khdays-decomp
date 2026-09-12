/* func_ov008_02079534 -- Ov008_MissionLobbyJoin: the lobby state that settles
 * the local join packet.  With the session ready, the local slot's packet
 * (+0x4ac, 6 bytes per player, slot from OS_IsTickAvailable) drops its pending
 * bit and is copied into the join packet (+0x4e0).  Otherwise, while the list
 * header word (+0x4a0) is set, the local player's packet either has the
 * pending bit -- then the header is cleared -- or is copied into the join
 * packet; and with the header clear the join packet is sent on gate 0xd and the
 * state stays.  Any other path arms handler 0207a254 on gate 0xd (state 1) and
 * moves on to 0207a424.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define GATE_LOBBY 0xd

typedef struct Ov008JoinPacket {
    u8  nPlayer;              /* 0x00 */
    u8  bJoined : 1;          /* 0x01 bit 0 */
    u8  bPending : 1;         /*      bit 1 */
    u8  nSpare : 6;
    signed char nTarget;      /* 0x02: -1 = any */
    u8  nPad;                 /* 0x03 */
    u16 nArg;                 /* 0x04 */
} Ov008JoinPacket;

typedef struct MissionContext {
    u8  pad_0000[0x4a0];
    int nListHeader;          /* 0x4a0 */
    u8  pad_04a4[0x4ac - 0x4a4];
    Ov008JoinPacket aPacket[4]; /* 0x4ac: one per player */
    u8  pad_04c4[0x4e0 - 0x4c4];
    Ov008JoinPacket join;     /* 0x4e0 */
} MissionContext;

extern MissionContext *data_ov008_02090f24;
extern int  func_02030694(void);                                  /* Session_IsReady */
extern u16  OS_IsTickAvailable(void);                             /* local slot */
extern u32  func_02030788(void);                                  /* Session_GetLocalPlayerIndex */
extern void func_02031258(int nGate, void *pBuf, int nSize);      /* MsgQueue_SendGate */
extern void func_02023c14(int nState);                            /* StoreToGlobalPtr4Field28 */
extern void func_02030cf8(int nGate, void *pHandler);             /* StoreGlobalPtrArray4At0c */
extern void *func_ov008_0207a254(void);                           /* gate handler */
extern void *func_ov008_0207a424(void);                           /* next lobby state */

void *func_ov008_02079534(void)
{
    MissionContext *pCtx;

    if (func_02030694()) {
        data_ov008_02090f24->aPacket[OS_IsTickAvailable()].bPending = 0;
        pCtx = data_ov008_02090f24;
        pCtx->join = pCtx->aPacket[OS_IsTickAvailable()];
    } else {
        pCtx = data_ov008_02090f24;
        if (pCtx->nListHeader != 0) {
            if (pCtx->aPacket[func_02030788()].bPending) {
                pCtx->nListHeader = 0;
            } else {
                pCtx = data_ov008_02090f24;
                pCtx->join = pCtx->aPacket[func_02030788()];
            }
        }
        if (data_ov008_02090f24->nListHeader == 0) {
            data_ov008_02090f24->nListHeader = 0;
            func_02031258(GATE_LOBBY, &data_ov008_02090f24->join, sizeof(Ov008JoinPacket));
            return 0;
        }
    }
    func_02023c14(1);
    func_02030cf8(GATE_LOBBY, func_ov008_0207a254);
    return func_ov008_0207a424;
}
