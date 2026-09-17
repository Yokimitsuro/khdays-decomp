/* func_ov023_02087a48 -- Ov023_ActorSpawnEffect: spawn the effect an actor's member kind
 * calls for (02033d0c) at its entity position (+0x15e0; +0xa8).  The resource comes from
 * Ov023_ActorResourceId (02087870), 0x298 for index 8; indices 0 / 4 / 13, 1 / 5 and 2 / 6
 * pick a variant from the actor's alternation flag (+0x458: the flag plus 0, 6 or 2) and flip
 * the flag; other indices use variant 0. */
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

typedef struct Ov023Actor {
    u8   pad_0000[0x458];
    int  nAlternate;          /* 0x0458 */
    u8   pad_045c[0x15e0 - 0x45c];
    Ov023Entity *pEntity;     /* 0x15e0 */
} Ov023Actor;

extern int  func_ov023_02087870(Ov023Actor *pActor, int nIndex);   /* Ov023_ActorResourceId */
extern void func_02033d0c(int nResource, int nVariant, VecFx32 *pPos, int nArg); /* Effect_Spawn */

void func_ov023_02087a48(Ov023Actor *pActor, int nIndex)
{
    VecFx32 vPos;
    int nResource;
    int nVariant;
    int nFlip;

    vPos = pActor->pEntity->vPos;
    nVariant = 0;
    nResource = func_ov023_02087870(pActor, nIndex);
    switch (nIndex) {
    case 0:
    case 4:
    case 13:
        /* the variant is the alternate itself; the null-based pointer sum is what keeps
         * mwcc's `add r5, r1, #0` (a plain read folds into the load) */
        nVariant = (int)((u8 *)0 + pActor->nAlternate);
        nFlip = 0;
        if (pActor->nAlternate == 0) {
            nFlip = 1;
        }
        pActor->nAlternate = nFlip;
        break;
    case 2:
    case 6:
        nVariant = pActor->nAlternate + 2;
        pActor->nAlternate = pActor->nAlternate == 0;
        break;
    case 1:
    case 5:
        nVariant = pActor->nAlternate + 6;
        pActor->nAlternate = pActor->nAlternate == 0;
        break;
    case 8:
        nResource = 0x298;
        break;
    }
    func_02033d0c(nResource, nVariant, &vPos, 0);
}
