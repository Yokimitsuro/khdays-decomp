/* func_ov015_0207fb8c -- Ov015_PickupShow: the pickup's show handler.  With a model
 * (+0x2c) it is submitted to the renderer under the kind's table byte (ov002 0207285c)
 * and its binding byte 1 set to 5.  The collidable flag (bit 3 of +0x12) is then decided:
 * off once the pickup was collected (bit 1 of +0x14d) or, for a pickup that reveals a
 * linked object (bit 7 clear), unless the first link key (+0x14e) resolves to a record
 * (ov002 02074460) -- then the linked object's node is hidden (ov002 02073ed0, show 0,
 * priority -1) and the pickup stays collidable.
 * Finally the model's sequence is started at the kind's spin speed (table 020828d8 by the
 * class's kind byte +0x84, << 12) with the pickup's rise speed (+0x138). */
typedef signed char    s8;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

extern int  func_ov002_0207285c(int nKind);                          /* kind -> table byte */
extern void func_0202ba9c(void *pNode, u16 nId, int nArg, void *pParams); /* Render_SubmitNode */
extern void func_02029438(void *pBinding, int nIndex, u8 nValue);   /* Actor_SetBindingByte */
extern int  func_ov002_02074460(int nKey);                           /* record index of a keyed object */
extern void func_ov002_02073ed0(int nKey, int bShow, int nPriority); /* show / hide a keyed object's node */
extern void func_ov015_0207fa40(void *pPickup, void *pSequence, int nArg, int nSpin, int nRise); /* Ov015_StoreArgsRunTwoSubActionsIfFlag4 */
extern u8   data_ov015_020828d8[];                                   /* per-kind pickup parameters, 8 bytes each */

typedef struct Ov015PickupDef {
    u8   pad_00[0x84];
    u8   nKind;               /* 0x84 */
} Ov015PickupDef;

typedef struct Ov015Pickup {
    u8   pad_000[8];
    Ov015PickupDef *pDef;     /* 0x008 */
    u8   pad_00c[4];
    u8   nKind;               /* 0x010 */
    u8   pad_011;
    u16  nFlags;              /* 0x012: bit 3 collidable */
    u8   pad_014[0x2c - 0x14];
    u8  *pModel;              /* 0x02c */
    u8   pad_030[0x138 - 0x30];
    int  nRiseSpeed;          /* 0x138 */
    u8   pad_13c[0x14d - 0x13c];
    u8   nStateBits;          /* 0x14d: bit 1 collected, bit 7 no linked object */
    short aLinkKey[2];        /* 0x14e: keys of the objects revealed on collection */
} Ov015Pickup;

void func_ov015_0207fb8c(Ov015Pickup *pPickup)
{
    Ov015PickupDef *pDef;
    int bCollidable;

    bCollidable = 1;
    pDef = pPickup->pDef;
    if (pPickup->pModel != 0) {
        func_0202ba9c(pPickup->pModel, func_ov002_0207285c(pPickup->nKind), 0, 0);
        func_02029438(pPickup->pModel + 0x11c, 1, 5);
    }
    if (pPickup->nStateBits & 2) {
        bCollidable = 0;
    } else if ((pPickup->nStateBits & 0x80) == 0) {
        bCollidable = 0;
        if (pPickup->aLinkKey[0] >= 0 && func_ov002_02074460(pPickup->aLinkKey[0]) >= 0) {
            func_ov002_02073ed0(pPickup->aLinkKey[0], 0, -1);
            bCollidable = 1;
        }
    }
    if (bCollidable) {
        pPickup->nFlags |= 8;
    } else {
        pPickup->nFlags &= ~8;
    }
    if (pPickup->pModel != 0) {
        func_ov015_0207fa40(pPickup, pPickup->pModel + 0x10, 0, data_ov015_020828d8[pDef->nKind * 8] << 12, pPickup->nRiseSpeed);
    }
}
