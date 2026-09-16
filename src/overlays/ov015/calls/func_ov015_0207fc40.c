/* func_ov015_0207fc40 -- Ov015_PickupRequestTake: hit handler of an idle pickup (+0x14c
 * == 0): unless a panel is open (ov002 020573cc), send a take request (kind 0x10: type 1
 * plus the toucher's player byte) through ov002 020766e0 and, once it is accepted, move
 * the pickup to the "requested" state (+0x14c = 1).  Always returns 0 (no hit consumed). */
typedef unsigned char  u8;
typedef unsigned int   u32;

extern int func_ov002_020573cc(void);                                 /* a panel is open */
extern int func_ov002_020766e0(void *pPiece, void *pMessage, int nKind); /* queue a message on the piece */

typedef struct Ov015Pickup {
    u8  pad_000[0x14c];
    u8  nState;               /* 0x14c: 0 idle, 1 take requested */
} Ov015Pickup;

typedef struct Ov015TakeRequest {
    u8  nType;                /* 0x00: 1 */
    u8  pad_01[3];
    int nZero4;               /* 0x04 */
    int nZero8;               /* 0x08 */
    u8  nPlayer;              /* 0x0c */
    u8  pad_0d[3];
} Ov015TakeRequest;

int func_ov015_0207fc40(Ov015Pickup *pPickup, u8 *pToucher, int nArg2, int nArg3)
{
    Ov015TakeRequest request;

    if (pPickup->nState != 0) {
        return 0;
    }
    if (func_ov002_020573cc() != 0) {
        return 0;
    }
    request.nType = 1;
    request.nPlayer = *pToucher;
    request.nZero4 = 0;
    request.nZero8 = 0;
    if (func_ov002_020766e0(pPickup, &request, 0x10) != 0) {
        pPickup->nState = 1;
    }
    return 0;
}
