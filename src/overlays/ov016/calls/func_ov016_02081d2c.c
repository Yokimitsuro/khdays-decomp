/* func_ov016_02081d2c -- Ov016_KickableStep: state function of a kickable.  Sync bit 0 (a
 * refresh request) is consumed together with bit 4; the frame delta (+0x64c) is zeroed.  On a
 * peer (local player index != 0, 02030788) with a received velocity (sync bit 1) a type-3
 * acknowledge message (kind 6, the local player) is queued (ov002 020766e0) -- staying (0)
 * until it goes out -- then the transform (+0x4a4) is put at the received velocity vector
 * (+0x640, 0202b450), the position (+0x488) reloaded from the rest position (+0x54c) and sync
 * bits 1 / 2 and kick flag bit 2 dropped.  Unless a kick target is pending and unresolved
 * (bits 8 / 9 of +0x464), a kicked kickable (bit 2) or one in mode 2 (bit 1 of +0x20) runs the
 * knockback step (ov002 0207caa4 on the speeds +0x1c, delta out to +0x64c): a result of 1
 * (landed) reloads the position from the rest position and, on the host, drops the host's bit
 * from the ack mask (+0x61d); a result of 2 (done) drops the kicked flag, replaces sync bit 3
 * by bit 2 (velocity to send) and, outside a session (bit 2 of the session bits 0204c240),
 * drops sync bit 4.  Finally the host, while bit 2 is set, queues the rest position as a
 * type-6 velocity message (kind 10, halfwords of the fx32 >> 4) unless one is already pending
 * (bit 3) -- moving bit 2 to bit 3 once it goes out -- and acknowledges itself
 * (Ov016_KickableAckPeer 02081624).  Always 0. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov016PeerMessage {
    u8   nType;               /* 0x00: 3 */
    u8   pad_01[3];
    u8   nPeer;               /* 0x04 */
    u8   pad_05;
} Ov016PeerMessage;

typedef struct Ov016VelocityMessage {
    u8   nType;               /* 0x00: 6 */
    u8   pad_01[3];
    short x;                  /* 0x04 */
    short y;                  /* 0x06 */
    short z;                  /* 0x08 */
} Ov016VelocityMessage;

typedef struct Ov016Kickable {
    u8   pad_000[0x1c];
    u16  nSpeedA;             /* 0x01c */
    u16  nSpeedB;             /* 0x01e */
    u8   nMode;               /* 0x020: bit 1 = mode 2 */
    u8   pad_021[0x464 - 0x21];
    u16  nKickFlags;          /* 0x464: bit 2 kicked, bit 8 target pending, bit 9 target resolved */
    u8   pad_466[0x488 - 0x466];
    VecFx32 position;         /* 0x488 */
    u8   pad_494[0x4a4 - 0x494];
    u8   transform[0x54c - 0x4a4]; /* 0x4a4 */
    VecFx32 rest;             /* 0x54c */
    u8   pad_558[0x61c - 0x558];
    u8   nSyncFlags;          /* 0x61c: bit 0 refresh, bit 1 velocity received, bit 2 velocity to send, bit 3 velocity pending, bit 4 */
    u8   nAckMask;            /* 0x61d */
    u8   pad_61e[0x640 - 0x61e];
    VecFx32 velocity;         /* 0x640 */
    VecFx32 delta;            /* 0x64c */
} Ov016Kickable;

extern int  func_02030788(void);                                      /* Session_GetLocalPlayerIndex */
extern int  func_ov002_020766e0(void *pPiece, void *pMessage, int nKind); /* queue a message on the piece */
extern void func_0202b450(void *pTransform, VecFx32 *pVec);           /* Actor_SetVecAndSyncChild */
extern int  func_ov002_0207caa4(void *pPiece, void *pSpeeds, VecFx32 *pOutDelta); /* knockback step */
extern int  func_ov016_02081624(Ov016Kickable *pSelf, int nPeer);     /* Ov016_KickableAckPeer */
extern VecFx32 data_02041dc8;                                         /* kVecZero */
extern u8   data_0204c240;                                            /* session bits */

void *func_ov016_02081d2c(Ov016Kickable *pSelf)
{
    Ov016VelocityMessage velocity;
    Ov016PeerMessage peer;
    u16 nFlags;
    int nResult;

    if (pSelf->nSyncFlags & 1) {
        pSelf->nSyncFlags &= ~1;
        pSelf->nSyncFlags &= ~0x10;
    }
    pSelf->delta = data_02041dc8;
    if (func_02030788() != 0 && (pSelf->nSyncFlags & 2)) {
        peer.nType = 3;
        peer.nPeer = func_02030788();
        if (func_ov002_020766e0(pSelf, &peer, 6) == 0) {
            return 0;
        }
        func_0202b450(pSelf->transform, &pSelf->velocity);
        pSelf->position = pSelf->rest;
        pSelf->nSyncFlags &= ~2;
        pSelf->nSyncFlags &= ~4;
        pSelf->nKickFlags &= ~4;
    }
    nFlags = pSelf->nKickFlags;
    if (((nFlags & 0x100) == 0 || (nFlags & 0x200) != 0) && ((nFlags & 4) != 0 || (pSelf->nMode & 2) != 0)) {
        nResult = func_ov002_0207caa4(pSelf, &pSelf->nSpeedA, &pSelf->delta);
        if (nResult == 1) {
            pSelf->position = pSelf->rest;
            if (func_02030788() == 0) {
                pSelf->nAckMask &= ~(1 << func_02030788());
            }
        } else if (nResult == 2) {
            pSelf->nKickFlags &= ~4;
            pSelf->nSyncFlags &= ~8;
            pSelf->nSyncFlags |= 4;
            if ((data_0204c240 & 4) == 0) {
                pSelf->nSyncFlags &= ~0x10;
            }
        }
    }
    if (func_02030788() == 0 && (pSelf->nSyncFlags & 4)) {
        if ((pSelf->nSyncFlags & 8) == 0) {
            velocity.nType = 6;
            velocity.x = pSelf->rest.x >> 4;
            velocity.y = pSelf->rest.y >> 4;
            velocity.z = pSelf->rest.z >> 4;
            if (func_ov002_020766e0(pSelf, &velocity, 10) != 0) {
                pSelf->nSyncFlags |= 8;
                pSelf->nSyncFlags &= ~4;
            }
        }
        func_ov016_02081624(pSelf, func_02030788());
    }
    return 0;
}
