/* func_ov023_02087870 -- Ov023_ActorResourceId: re-place an actor's entity (0202de3c on the
 * entity slot at +0x15e0, then 0202b450 with its own position) and return the id of the
 * resource its member kind needs.  Without a member block (+0x162c) that is 0; otherwise the
 * block's kind byte (+0x83) picks the pair -- 0: 0x18c / 0x198, 1: 0x18d / 0x199, 4: 0x18e /
 * 0x19a, 9: 0x18f / 0x19b, 7: 0x190 / 0x19c, 8: 0x191 / 0x19d, 2: 0x192 / 0x19e, 5: 0x193 /
 * 0x19f, 6: 0x194 / 0x1a0, 3: 0x195 / 0x1a1, 10: 0x196 / 0x1a2, others 0x18d / 0x199 -- the
 * first for actor indices below 4, the second from 4 on; except for kind 10, an extra set
 * (data_ov023_0208a784 byte 0) overrides with 0x197 / 0x1a3. */
typedef unsigned char  u8;

typedef struct VecFx32 {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
    int  z;                   /* 0x08 */
} VecFx32;

typedef struct Ov023Entity {
    u8   pad_00[0xa8];
    VecFx32 vPos;             /* 0xa8 */
} Ov023Entity;

typedef struct Ov023MemberBlock {
    u8   pad_00[0x83];
    u8   nKind;               /* 0x83 */
} Ov023MemberBlock;

typedef struct Ov023Actor {
    u8   pad_0000[0x15e0];
    Ov023Entity *pEntity;     /* 0x15e0 */
    u8   pad_15e4[0x162c - 0x15e4];
    Ov023MemberBlock *pMember; /* 0x162c */
} Ov023Actor;

typedef struct Ov023SceneRoot {
    u8   bExtraRequested;     /* 0x00 */
    u8   pad_01[3];
    void *pScene;             /* 0x04 */
} Ov023SceneRoot;

extern void  func_0202de3c(Ov023Entity **ppEntity, int nArg);      /* re-place an entity */
extern void  func_0202b450(Ov023Entity *pEntity, VecFx32 *pPos);   /* Entity_SetPositionNow */
extern Ov023SceneRoot data_ov023_0208a784;

int func_ov023_02087870(Ov023Actor *pActor, int nIndex)
{
    VecFx32 vPos;
    int nResource;
    int bLow;

    vPos = pActor->pEntity->vPos;
    nResource = 0;
    func_0202de3c(&pActor->pEntity, 0);
    func_0202b450(pActor->pEntity, &vPos);
    if (pActor->pMember != 0) {
        bLow = nIndex < 4;
        switch (pActor->pMember->nKind) {
        case 0:
            nResource = bLow ? 0x18c : 0x198;
            break;
        case 1:
            nResource = bLow ? 0x18d : 0x199;
            break;
        case 4:
            nResource = bLow ? 0x18e : 0x19a;
            break;
        case 9:
            nResource = bLow ? 0x18f : 0x19b;
            break;
        case 7:
            nResource = bLow ? 0x190 : 0x19c;
            break;
        case 8:
            nResource = bLow ? 0x191 : 0x19d;
            break;
        case 2:
            nResource = bLow ? 0x192 : 0x19e;
            break;
        case 5:
            nResource = bLow ? 0x193 : 0x19f;
            break;
        case 6:
            nResource = bLow ? 0x194 : 0x1a0;
            break;
        case 3:
            nResource = bLow ? 0x195 : 0x1a1;
            break;
        case 10:
            return bLow ? 0x196 : 0x1a2;
        default:
            nResource = bLow ? 0x18d : 0x199;
            break;
        }
        if (data_ov023_0208a784.bExtraRequested != 0) {
            nResource = bLow ? 0x197 : 0x1a3;
        }
    }
    return nResource;
}
