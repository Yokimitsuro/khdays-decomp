/* Ov022_StepSyncRequest -- advance one sync request through its phases.
 *
 * Phase 1 waits for the request's handle to be ready. Then, with the session
 * ready, the local player's bit is set in the seen bitmap at the request's
 * row and column and the request moves to phase 2; without a session the
 * request is marshalled and sent, and a refused send closes it (waiting
 * dropped, done raised, phase 3). Phase 2 closes it the same way once every
 * player's bit is in, clearing the bitmap cell. Phase 3 waits for the
 * acknowledged bit and then clears the request back to idle.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* Ov022SyncRequest: one of the twelve 0x38-byte requests */
struct SyncRequest {
    u8 bWaiting : 1;             /* 0x00 bit 0 */
    u8 bDone : 1;                /* 0x00 bit 1 */
    u8 bAcked : 1;               /* 0x00 bit 2 */
    u8 nRest00 : 5;
    u8 nRow;                     /* 0x01 */
    u8 nCol;                     /* 0x02 */
    u8 nPhase;                   /* 0x03 */
    u8 pad04[0x32];
    u16 nMsgId;                  /* 0x36 id the send answered */
};

/* Ov022SyncSession: the session block the requests share */
struct SyncSession {
    u8 pad000[0x2b0];
    u8 aSeen[8][3];              /* 0x2b0 one bit per player */
};

#define REQ_ACKED 0x4
#define PHASE_IDLE 0
#define PHASE_SEND 1
#define PHASE_WAIT 2
#define PHASE_CLOSE 3
#define MSG_ID_NONE 0xffff

extern struct SyncSession *data_ov022_020b2eb8;

extern int func_ov022_020b1224(struct SyncRequest *pReq);
extern int func_02030694(void);
extern int func_02030788(void);
extern void func_ov022_020b0eb8(struct SyncRequest *pReq);
extern int func_01fff974(void);

void func_ov022_020b10c8(struct SyncRequest *pReq)
{
    struct SyncSession *pSession;
    u8 *pRow;
    int nCol;

    pSession = data_ov022_020b2eb8;
    switch (pReq->nPhase) {
    case PHASE_SEND:
        if (func_ov022_020b1224(pReq) == 0) {
            return;
        }
        if (func_02030694() == 0) {
            func_ov022_020b0eb8(pReq);
            if (pReq->nMsgId == MSG_ID_NONE) {
                return;
            }
            pReq->bWaiting = 0;
            pReq->bDone = 1;
            pReq->nPhase = PHASE_CLOSE;
            return;
        }
        pSession->aSeen[pReq->nRow][pReq->nCol] |= 1 << func_02030788();
        pReq->nPhase = PHASE_WAIT;
        break;
    case PHASE_WAIT:
        pRow = pSession->aSeen[pReq->nRow];
        nCol = pReq->nCol;
        if (pRow[nCol] == func_01fff974()) {
            pRow[nCol] = 0;
            pReq->bWaiting = 0;
            pReq->bDone = 1;
            pReq->nPhase = PHASE_CLOSE;
        }
        break;
    case PHASE_CLOSE:
        if ((*(u8 *)pReq & REQ_ACKED) != 0) {
            *(u8 *)pReq = 0;
            pReq->nPhase = PHASE_IDLE;
        }
        break;
    }
}
