/* Ov021_PrizeBoxRefresh -- Ov021_PrizeBoxRefresh: refresh handler of the prize box.  Unless the
 * box has been opened (bit 0 of +0x1b9) it submits the render node (+0x2c, 0202ba9c) on the
 * bucket's seat slot (ov002 0207285c) and sets binding byte 3 of the +0x148 block (02029438)
 * to 1 in mission 0x41d (ov002 0206b84c), 3 elsewhere.  Then the host (02030788 == 0), when
 * the box's prize (the class entry at +0x78 + 6 * the prize index +0x1be) is a keyed object
 * (type 2 with a valid key) that has a record (ov002 02074460), hides that object
 * unless it was already revealed (bit 1 of +0x1b9; ov002 02073ed0) and moves it to the box's
 * position (ov002 02073f28). */

#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Ov021Prize {
    char  nType;              /* 0x00: 0 item, 1 munny, 2 keyed object, 3 nothing */
    u8    pad_01;
    short nValue;             /* 0x02: item key, amount or object key */
    u8    bFlag;              /* 0x04 */
    u8    pad_05;
} Ov021Prize;

typedef struct Ov021PrizeBoxDef {
    u8   pad_00[0x78];
    Ov021Prize aPrize[1];     /* 0x78: one per box of the class */
} Ov021PrizeBoxDef;

typedef struct Ov021PrizeBox {
    u8   pad_000[8];
    Ov021PrizeBoxDef *pDef;   /* 0x008 */
    u8   pad_00c[4];
    u8   nRoom;             /* 0x010 */
    u8   pad_011[0x2c - 0x11];
    u8   renderNode[0xe0 - 0x2c]; /* 0x02c: the binding block sits at +0x148 */
    VecFx32 position;         /* 0x0e0 */
    u8   pad_0ec[0x148 - 0xec];
    u8   binding[0x1b9 - 0x148]; /* 0x148 */
    u8   nFlags;              /* 0x1b9: bit 0 opened, bit 1 object revealed */
    u8   pad_1ba[4];
    char nPrize;              /* 0x1be: index into the class's prize list */
} Ov021PrizeBox;

extern int   Ov002_GetCtxTableByte(int nRoom);                       /* bucket -> seat slot */
extern void  Render_SubmitNode(void *pNode, int nId, int nArg, void *pParams); /* Render_SubmitNode */
extern int   Ov002_GetStateWord(void);                              /* the mission id */
extern void  Actor_SetBindingByte(void *pBinding, int nIndex, u8 nValue);   /* Actor_SetBindingByte */
extern int   Session_GetLocalPlayerIndex(void);                                    /* Session_GetLocalPlayerIndex */
extern int   Ov002_FindKeyIndex(int nKey);                          /* record index of a keyed object */
extern void  Ov002_SetKeyNodeVisible(int nKey, int bShow, int nPriority); /* show / hide a keyed object's node */
extern void  Ov002_SetEntryPosition(int nKey, VecFx32 *pPos);           /* move a keyed object */

void Ov021_PrizeBoxRefresh(Ov021PrizeBox *pSelf)
{
    Ov021PrizeBoxDef *pDef;

    pDef = pSelf->pDef;
    if ((pSelf->nFlags & 1) == 0) {
        Render_SubmitNode(pSelf->renderNode, (u16)(Ov002_GetCtxTableByte(pSelf->nRoom)), 0, 0);
        if (Ov002_GetStateWord() == 0x41d) {
            Actor_SetBindingByte(pSelf->binding, 3, 1);
        } else {
            Actor_SetBindingByte(pSelf->binding, 3, 3);
        }
    }
    if (Session_GetLocalPlayerIndex() != 0) {
        return;
    }
    if (pDef->aPrize[pSelf->nPrize].nType != 2) {
        return;
    }
    if (pDef->aPrize[pSelf->nPrize].nValue < 0) {
        return;
    }
    if (Ov002_FindKeyIndex(pDef->aPrize[pSelf->nPrize].nValue) < 0) {
        return;
    }
    if ((pSelf->nFlags & 2) == 0) {
        Ov002_SetKeyNodeVisible(pDef->aPrize[pSelf->nPrize].nValue, 0, -1);
    }
    Ov002_SetEntryPosition(pDef->aPrize[pSelf->nPrize].nValue, &pSelf->position);
}
