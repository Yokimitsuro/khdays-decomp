/* func_ov023_02085d30 -- Ov023_CmdAttachWeapons: script command that gives a party actor its
 * weapon actors.  Operand 0 is the actor (resolved by 02020d10), operand 1 the motion variant.
 * The actor's kind comes from its session seat (020315c0; 0 for an empty one) and its entity
 * gets flag bit 4 (0202bfcc +4).  Copies of the weapon resource table (data_ov023_02089e10,
 * two per kind) and the weapon motion table (data_ov023_02089eb0, two per kind and variant)
 * are taken; then for weapon 0 and, only for kinds 1 / 2 / 7 / 9 / 0x13, weapon 1: actor
 * actor + 4 * (weapon + 1) is attached to the actor with the kind's resource (0202bb7c), its
 * model placed at the origin (020887dc with the actor's model id 0202bf84) and linked to the
 * actor (020888b8), and, when the motion table has an entry, the motion "mi/mo/mu.p2"
 * (variant 0) or "mi/mo/win_we.p2" (variant 1) started on it (02089390).  Returns 1. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct VecFx32 {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
    int  z;                   /* 0x08 */
} VecFx32;

typedef struct Ov023SessionSlot {
    int  nField00;            /* 0x00 */
    int  nMemberKind;         /* 0x04 */
} Ov023SessionSlot;

typedef struct Ov023Entity {
    int  nFlags;              /* 0x00 */
    u16  wFlags;              /* 0x04 */
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

typedef struct Ov023WeaponResTable {
    void *apRes[20][2];       /* 0x00: by kind and weapon */
} Ov023WeaponResTable;

typedef struct Ov023WeaponMotionTable {
    int  aMotion[20][2][2];   /* 0x00: by kind, variant and weapon */
} Ov023WeaponMotionTable;

extern int   func_02021980(Ov023ScriptCtx *pCtx, void *pOperand);  /* ScriptVm_ReadOperandInt */
extern int   func_02020d10(Ov023ScriptCtx *pCtx, int nIndex);      /* resolve an actor index */
extern Ov023SessionSlot *func_020315c0(int nSlot);                  /* Session_GetSlotIfOccupied */
extern Ov023Entity *func_0202bfcc(u16 nEntity);                     /* Entity_Get */
extern void  func_0202bb7c(u16 nEntity, u16 nParent, void *pRes);  /* Entity_Attach */
extern int   func_0202bf84(u16 nEntity);                            /* Entity_GetModelId */
extern void  func_ov023_020887dc(Ov023Actor *pActor, char *pszAnchor, const VecFx32 *pPos, int nMode, int nActor); /* Ov023_PlaceActorModel */
extern void  func_ov023_020888b8(Ov023Actor *pActor, Ov023Actor *pParent, int nActor); /* Ov023_LinkActor */
extern void  func_ov023_02089390(Ov023Actor *pActor, char *pszMotion, int nMotion, int nA, int nB); /* Ov023_StartActorMotion */
extern const Ov023WeaponResTable data_ov023_02089e10;               /* weapon resources */
extern const Ov023WeaponMotionTable data_ov023_02089eb0;            /* weapon motions */
extern const VecFx32 data_02041dc8;                                 /* the zero vector */
extern const u8 data_ov023_0208a5f4[];                              /* "mi/mo/mu.p2" */
extern const u8 data_ov023_0208a600[];                              /* "mi/mo/win_we.p2" */

int func_ov023_02085d30(Ov023ScriptCtx *pCtx, u8 *pOperand)
{
    Ov023WeaponResTable resources;
    Ov023WeaponMotionTable motions;
    char szMotion[0x20];
    int  nVariant;
    int  nWeapon;
    void **ppRes;
    int  nActorOffset;
    int  nActor;
    int  nKind;
    int  *pMotion;
    int  nWeaponActor;
    int  nWeaponOffset;
    Ov023SessionSlot *pSlot;

    nActor = func_02021980(pCtx, pOperand);
    nVariant = func_02021980(pCtx, pOperand + 8);
    resources = data_ov023_02089e10;
    motions = data_ov023_02089eb0;
    nActor = func_02020d10(pCtx, nActor);
    pSlot = func_020315c0(nActor);
    if (pSlot == 0) {
        nKind = 0;
    } else {
        nKind = pSlot->nMemberKind;
    }
    func_0202bfcc((u16)nActor)->wFlags |= 0x10;
    nWeapon = 0;
    ppRes = resources.apRes[nKind];
    pMotion = motions.aMotion[nKind][nVariant];
    nActorOffset = nActor * sizeof(Ov023Actor);
    do {
        if (nWeapon == 1) {
            switch (nKind) {
            case 1:
            case 2:
            case 7:
            case 9:
            case 0x13:
                break;
            default:
                return 1;
            }
        }
        nWeaponActor = nActor + (nWeapon + 1) * 4;
        func_0202bb7c((u16)nWeaponActor, (u16)nActor, *ppRes);
        nWeaponOffset = nWeaponActor * sizeof(Ov023Actor);
        func_ov023_020887dc((Ov023Actor *)((u8 *)pCtx->pEvent->pActors + nWeaponOffset), 0, &data_02041dc8,
                            func_0202bf84((u16)nActor), nWeaponActor);
        func_ov023_020888b8((Ov023Actor *)((u8 *)pCtx->pEvent->pActors + nWeaponOffset),
                            (Ov023Actor *)((u8 *)pCtx->pEvent->pActors + nActorOffset), nWeaponActor);
        if (*pMotion != -1) {
            switch (nVariant) {
            case 0: {
                u32 nRemaining;
                const u8 *pSrc;
                u8 *pDst;

                pSrc = data_ov023_0208a5f4;
                pDst = (u8 *)szMotion;
                nRemaining = 12;
                do {
                    *pDst = *pSrc;
                    pSrc++;
                    pDst++;
                    nRemaining--;
                } while (nRemaining != 0);
                break;
            }
            case 1: {
                u32 nRemaining;
                const u8 *pSrc;
                u8 *pDst;

                pSrc = data_ov023_0208a600;
                pDst = (u8 *)szMotion;
                nRemaining = 16;
                do {
                    *pDst = *pSrc;
                    pSrc++;
                    pDst++;
                    nRemaining--;
                } while (nRemaining != 0);
                break;
            }
            }
            func_ov023_02089390((Ov023Actor *)((u8 *)pCtx->pEvent->pActors + nWeaponOffset), szMotion, *pMotion, 0, 0);
        }
        pMotion++;
        ppRes++;
        nWeapon++;
    } while (nWeapon < 2);
    return 1;
}
