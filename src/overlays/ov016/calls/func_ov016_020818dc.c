/* func_ov016_020818dc -- Ov016_KickableReceiveHit: the kickable's hit handler (definition slot
 * +0x44, called with mode 0 and a hit record {position, range, source}).  Any other mode is
 * refused (-1).  A hit from the source that already kicked it (+0x62c) while the kick is
 * pending (kick flag bit 8) answers whether the kick has not been resolved yet (bit 9 clear);
 * a kickable already in flight (bit 0) ignores hits.  Otherwise, when the hit lands within its
 * range of the rest position (+0x54c, 01ff8e94 = VEC_Distance), the source is remembered and
 * a kind-0x10 message {4, hit position} is queued on the piece (ov002 020766e0).  0 either way. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov016Hit {
    VecFx32 position;         /* 0x00 */
    int nRange;               /* 0x0c */
    void *pSource;            /* 0x10 */
} Ov016Hit;

typedef struct Ov016KickMessage {
    u8 nKind;                 /* 0x00 */
    u8 pad_01[3];
    VecFx32 position;         /* 0x04 */
} Ov016KickMessage;

typedef struct Ov016Kickable {
    u8 pad_000[0x464];
    u16 nKickFlags;           /* 0x464: bit 0 in flight, bit 8 kick pending, bit 9 kick resolved */
    u8  pad_466[0x54c - 0x466];
    VecFx32 rest;             /* 0x54c */
    u8  pad_558[0x62c - 0x558];
    void *pKicker;            /* 0x62c: source of the last kick */
} Ov016Kickable;

extern int func_01ff8e94(VecFx32 *pA, VecFx32 *pB);                   /* VEC_Distance */
extern int func_ov002_020766e0(void *pPiece, void *pMessage, int nKind); /* queue a message on the piece */

int func_ov016_020818dc(Ov016Kickable *pSelf, int nMode, Ov016Hit *pHit)
{
    Ov016KickMessage message;

    if (nMode == 0) {
        if (pSelf->pKicker == pHit->pSource && (pSelf->nKickFlags & 0x100)) {
            return (pSelf->nKickFlags & 0x200) == 0;
        }
        if (pSelf->nKickFlags & 1) {
            return 0;
        }
        if (pHit->nRange < func_01ff8e94(&pHit->position, &pSelf->rest)) {
            return 0;
        }
        pSelf->pKicker = pHit->pSource;
        message.nKind = 4;
        message.position = pHit->position;
        func_ov002_020766e0(pSelf, &message, 0x10);
        return 0;
    }
    return -1;
}
