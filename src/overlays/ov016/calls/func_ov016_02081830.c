/* func_ov016_02081830 -- Ov016_KickableReturnHome: put the kickable back.  When it has a second
 * GameState field (+0x630 != 0xffff) and that flag is already set the kickable is gone for good
 * and nothing happens; otherwise its kick is cleared (+0x62c = 0, the target +0x474 reset to the
 * home position +0x634, kick flags +0x464 = 0, piece flag bit 3 set, ack mask +0x61d = 0).  The
 * transform (+0x4a4) is then put at the target (0202b450), the position (+0x488) reloaded from
 * the rest position (+0x54c), kind-0 kickables get kick flag bit 2 and a body value of 0x19a
 * (+0x5c), and sync flag bit 0 (+0x61c) is raised. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov016KickableDef {
    u8 pad_00[0x7c];
    u8 nKind;                 /* 0x7c */
} Ov016KickableDef;

typedef struct Ov016Kickable {
    u8 pad_000[0x8];
    Ov016KickableDef *pDef;   /* 0x08 */
    u8 pad_00c[0x6];
    u16 nPieceFlags;          /* 0x12 */
    u8  pad_014[0x24 - 0x14];
    u8  body[0x5c - 0x24];    /* 0x24: the actor body */
    int nBodyWord5c;          /* 0x5c: body + 0x38 */
    u8  pad_060[0x464 - 0x60];
    u16 nKickFlags;           /* 0x464 */
    u8  pad_466[0x474 - 0x466];
    VecFx32 target;           /* 0x474 */
    u8  pad_480[0x488 - 0x480];
    VecFx32 position;         /* 0x488 */
    u8  pad_494[0x4a4 - 0x494];
    u8  transform[0x54c - 0x4a4];  /* 0x4a4 */
    VecFx32 rest;             /* 0x54c */
    u8  pad_558[0x61c - 0x558];
    u8  nSyncFlags;           /* 0x61c */
    u8  nAckMask;             /* 0x61d */
    u8  pad_61e[0x62c - 0x61e];
    int nWord62c;             /* 0x62c */
    u16 nField2;              /* 0x630: second GameState field */
    u8  nBit2;                /* 0x632 */
    u8  pad_633;
    VecFx32 home;             /* 0x634 */
} Ov016Kickable;

extern int  func_020235d0(u16 nField, u8 nBit);                      /* GameState_GetField */
extern void func_0202b450(void *pTransform, VecFx32 *pVec);          /* Actor_SetVecAndSyncChild */

void func_ov016_02081830(Ov016Kickable *pSelf)
{
    Ov016KickableDef *pDef;

    pDef = pSelf->pDef;
    if (pSelf->nField2 != 0xffff) {
        if (func_020235d0(pSelf->nField2, pSelf->nBit2) != 0) {
            return;
        }
        pSelf->nWord62c = 0;
        pSelf->target = pSelf->home;
        pSelf->nKickFlags = 0;
        pSelf->nPieceFlags |= 8;
        pSelf->nAckMask = 0;
    }
    func_0202b450(pSelf->transform, &pSelf->target);
    pSelf->position = pSelf->rest;
    if (pDef->nKind == 0) {
        pSelf->nKickFlags |= 4;
        pSelf->nBodyWord5c = 0x19a;
    }
    pSelf->nSyncFlags |= 1;
}
