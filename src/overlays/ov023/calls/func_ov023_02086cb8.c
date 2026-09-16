/* func_ov023_02086cb8 -- Ov023_CmdSeatMembers: script command that seats the party actors.
 * A copy of the 13 seat heights (data_ov023_02089ddc) is taken.  Without operand 0 all 13
 * seats are filled: actor i gets the chair resource (data_ov023_0208a660, 0202b914 1 / 0xd),
 * is placed on the spot "chair<i>" (Ov023_FormatSeatName 02086c90, 0202ba78) at the seat's
 * height + 0xda01 above the origin, and its model is placed at the entity's position
 * (0202bfcc +0xa8, 020887dc).  With operand 0 (the actor) and operand 1 (an extra height)
 * only that actor is moved to its chair spot (0202c3e4) raised by the extra, the seat height
 * and 0xda01 (0202b450).  Returns 1. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef signed short   s16;

typedef struct VecFx32 {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
    int  z;                   /* 0x08 */
} VecFx32;

typedef struct Ov023Operand {
    s16  nType;               /* 0x00 */
    u8   pad_02[6];
} Ov023Operand;               /* 0x08 */

typedef struct Ov023Entity {
    u8   pad_00[0xa8];
    VecFx32 vPos;             /* 0xa8 */
} Ov023Entity;

typedef struct Ov023Actor {
    u8   pad_0000[0x1a64];
} Ov023Actor;

typedef struct Ov023EventBlock {
    u8   pad_000[0x440];
    Ov023Actor *pActors;      /* 0x440 */
} Ov023EventBlock;

typedef struct Ov023ScriptCtx {
    u8   pad_000[0x128];
    Ov023EventBlock *pEvent;  /* 0x128 */
} Ov023ScriptCtx;

typedef struct Ov023SeatHeights {
    int  aHeight[13];         /* 0x00 */
} Ov023SeatHeights;

extern int   func_02021980(Ov023ScriptCtx *pCtx, Ov023Operand *pOperand);   /* ScriptVm_ReadOperandInt */
extern int   func_02021994(Ov023ScriptCtx *pCtx, Ov023Operand *pOperand);   /* ScriptVm_ReadOperandFx32 */
extern void  func_0202b914(u16 nEntity, void *pTable, int nA, int nB); /* Entity_BindResource */
extern char *func_ov023_02086c90(int nIndex);                       /* Ov023_FormatSeatName */
extern void  func_0201f924(char *pszDst, const char *pszSrc);       /* STD_CopyString */
extern void  func_0202ba78(u16 nEntity, u16 nMode, char *pszSpot, VecFx32 *pPos); /* Entity_SetPosition */
extern Ov023Entity *func_0202bfcc(u16 nEntity);                     /* Entity_Get */
extern void  func_ov023_020887dc(Ov023Actor *pActor, char *pszAnchor, VecFx32 *pPos, int nMode, int nActor); /* Ov023_PlaceActorModel */
extern void  func_0202c3e4(u16 nModel, char *pszSpot, VecFx32 *pOut); /* Model_GetSpotPosition */
extern void  func_0202b450(Ov023Entity *pEntity, VecFx32 *pPos);   /* Entity_SetPositionNow */
extern const Ov023SeatHeights data_ov023_02089ddc;                  /* the seat heights */
extern const VecFx32 data_02041dc8;                                 /* the zero vector */
extern char  data_ov023_0208a660[];                                 /* "/mi/ob/0C.z", the chair model */

int func_ov023_02086cb8(Ov023ScriptCtx *pCtx, Ov023Operand *pOperand)
{
    VecFx32 vPos;
    char szSpot[0x40];
    Ov023SeatHeights heights;
    int i;
    int nActor;
    int nExtra;
    Ov023Entity *pEntity;

    heights = data_ov023_02089ddc;
    if (pOperand->nType == 0) {
        VecFx32 vOffset;

        vOffset = data_02041dc8;
        for (i = 0; i < 13; i++) {
            func_0202b914((u16)i, data_ov023_0208a660, 1, 0xd);
            vOffset.y = heights.aHeight[i] + 0xda01;
            func_0201f924(szSpot, func_ov023_02086c90(i));
            func_0202ba78((u16)i, 0, szSpot, &vOffset);
            vPos = func_0202bfcc((u16)i)->vPos;
            func_ov023_020887dc(&pCtx->pEvent->pActors[i], 0, &vPos, 0, i);
        }
    } else {
        nExtra = func_02021994(pCtx, pOperand + 1);
        nActor = func_02021980(pCtx, pOperand);
        pEntity = func_0202bfcc((u16)nActor);
        func_0201f924(szSpot, func_ov023_02086c90(nActor));
        func_0202c3e4(0, szSpot, &vPos);
        vPos.y += nExtra + (heights.aHeight[nActor] + 0xda01);
        func_0202b450(pEntity, &vPos);
    }
    return 1;
}
