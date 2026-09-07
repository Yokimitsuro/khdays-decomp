/* ov022: turn the committed command into an action request.
 *
 * The per-frame tick runs this straight after the forced-state selector. It
 * clears the pending action, bails when the actor is locked out or when the
 * local player is in the mode that suppresses input, decodes the aim angle,
 * and then dispatches on the committed command kind: the attack path (8), the
 * ground and menu path (9) which can also become a block, a reaction or a
 * ready signal, and the shared magic and item path (0xb to 0xd).
 *
 * It is edge-triggered: whichever way it exits, it clears its own request bit
 * and resets the committed kind to 7.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct Equip;

struct Actor {
    unsigned long long nFlags;   /* 0x000 */
    u8 nOwner;                   /* 0x008 */
    u8 nId;                      /* 0x009 */
    u8 pad00a[0xe];
    u16 nButtons;                /* 0x018 */
    u16 nButtons2;               /* 0x01a */
    u16 nPendingAction;          /* 0x01c */
    u8 pad01e[0x446];
    unsigned long long nFlags2;  /* 0x464 */
    u8 pad46c[0x6a];
    signed char nCommandKind;    /* 0x4d6 */
    u8 pad4d7[1];
    u16 nCommandArg;             /* 0x4d8 */
    u16 nCommandArg2;            /* 0x4da */
    signed char nLatchedKind;    /* 0x4dc */
    u8 pad4dd[1];
    u16 nLatchedArg;             /* 0x4de */
    u16 nLatchedArg2;            /* 0x4e0 */
    u8 pad4e2[6];
    u8 bHudFlag : 1;             /* 0x4e8 bit 0 */
    u8 bMenuFlag : 1;
    u8 bActionRequest : 1;       /* bit 2 */
    u8 bIdleFlag : 1;
    u8 nRest4e8 : 4;
    u8 pad4e9[0xf];
    struct Equip *pEquip;        /* 0x4f8 */
    u8 pad4fc[0x198];
    u8 bSuppressDraw : 1;        /* 0x694 bit 0 */
    u8 nPad694 : 2;
    u8 bActionLocked : 1;        /* bit 3 */
    u8 nRest694 : 4;
    u8 pad695[0x6eb];
    int nComboLock;              /* 0xd80 */
    u8 padd84[0x1024];
    u8 reactionBlk;              /* 0x1da8 */
    u8 pad1da9[0x4df];
    u8 slotMask;                 /* 0x2288 */
    u8 pad2289[0x6f];
    u8 stateBlk;                 /* 0x22f8 */
    u8 pad22f9[0x477];
    signed char nKnockdownKind;  /* 0x2770 */
    u8 pad2771[0x34b];
    int nAimAngle;               /* 0x2abc */
};

extern u8 data_0204c240;
extern u8 data_0204be04;

extern int func_02030788(void);
extern int func_020208e0(void);
extern int func_ov022_020a0814(struct Actor *pActor);
extern void func_ov022_0209bdbc(struct Actor *pActor);
extern int func_ov022_020955b0(u8 *pBlk);
extern int func_ov022_0209fc78(struct Actor *pActor, int nSlot);
extern int func_ov002_0206e770(int nWhich);
extern int func_ov022_020ad1d0(struct Actor *pActor);
extern int func_ov002_02076c24(struct Equip *pEquip, u8 nId);
extern int func_ov022_0209bd04(struct Actor *pActor);
extern void func_ov022_0209bd10(struct Actor *pActor);
extern int func_ov022_02095524(u8 *pBlk);
extern int func_ov022_02095554(u8 *pBlk);
extern int func_ov022_02095450(u8 *pBlk);
extern int func_ov022_02090378(u8 *pMask);
extern int func_ov022_02093be0(u8 *pBlk);
extern int func_ov022_020b1554(u8 nId);

void func_ov022_020a31b4(struct Actor *pActor)
{
    int bTrigger;
    int bLocked;
    int nAim;

    bTrigger = 0;
    pActor->nPendingAction = 0;
    bLocked = 0;
    if ((pActor->nFlags & (1ULL << 8)) != 0) {
        return;
    }
    if ((pActor->nFlags & (1ULL << 17)) != 0) {
        return;
    }
    if ((pActor->nFlags & (1ULL << 45)) != 0
        || (pActor->nFlags & (1ULL << 24)) != 0) {
        bLocked = 1;
    }
    if (func_02030788() == 0
        && pActor->nOwner == func_02030788()
        && (data_0204c240 & 4) != 0
        && func_020208e0() == 2) {
        bLocked = 1;
    }
    if (bLocked != 0) {
        pActor->nButtons = 0;
        pActor->nButtons2 = 0;
        pActor->bActionRequest = 0;
        pActor->nCommandKind = 7;
        pActor->nAimAngle = -1;
        return;
    }

    pActor->nAimAngle = func_ov022_020a0814(pActor);
    if (pActor->nKnockdownKind == 5) {
        func_ov022_0209bdbc(pActor);
    }
    if (pActor->nAimAngle >= 0 && func_02030788() == 0) {
        pActor->nFlags2 |= (1ULL << 19);
    }
    if (func_ov022_020955b0(&pActor->stateBlk) == 0
        && pActor->bActionLocked == 0) {
        if ((pActor->nButtons & 1) != 0) {
            bTrigger = 1;
        }
        if (pActor->bActionRequest != 0) {
            if (pActor->nCommandKind != 7) {
                bTrigger = 1;
            }
            pActor->nButtons &= ~0xc03;
        }
    }

    if (bTrigger != 0) {
        switch (pActor->nCommandKind) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            break;
        case 9:
            if (func_ov022_0209fc78(pActor, -1) != 0
                && func_ov002_0206e770(0) == 0) {
                pActor->nPendingAction = 1;
            }
            if (pActor->nComboLock == 0) {
                nAim = func_ov022_020ad1d0(pActor);
                if (nAim != -1 && nAim != 0
                    && func_ov002_02076c24(pActor->pEquip, pActor->nId) != 0) {
                    if (func_ov022_0209bd04(pActor) == 0xb) {
                        func_ov022_0209bd10(pActor);
                    } else {
                        pActor->nPendingAction = 2;
                    }
                }
            }
            if (func_ov022_02095524(&pActor->stateBlk) != 0) {
                pActor->nPendingAction = 5;
            }
            if (func_ov022_02095554(&pActor->stateBlk) != 0) {
                pActor->nPendingAction = 6;
            }
            break;
        case 8:
            if (func_ov022_02095450(&pActor->stateBlk) == 0
                && func_ov022_02090378(&pActor->slotMask) != 0
                && func_ov022_02093be0(&pActor->reactionBlk) != 0
                && func_ov022_020b1554(pActor->nId) != 0
                && (pActor->nFlags & (1ULL << 4)) == 0
                && func_ov022_0209bd04(pActor) != 6) {
                pActor->nPendingAction = 4;
                pActor->nLatchedKind = pActor->nCommandKind;
                pActor->nLatchedArg = pActor->nCommandArg;
            }
            break;
        case 10:
            break;
        case 11:
        case 12:
        case 13:
            if ((pActor->nCommandKind != 13 || data_0204be04 == 0)
                && func_ov022_02095450(&pActor->stateBlk) == 0
                && func_ov022_02090378(&pActor->slotMask) != 0
                && func_ov022_02093be0(&pActor->reactionBlk) != 0
                && func_ov022_020b1554(pActor->nId) != 0
                && (pActor->nFlags & (1ULL << 4)) == 0) {
                pActor->nPendingAction = 3;
                pActor->nLatchedKind = pActor->nCommandKind;
                pActor->nLatchedArg = pActor->nCommandArg;
                pActor->nLatchedArg2 = pActor->nCommandArg2;
            }
            break;
        default:
            break;
        }
    }

    if (pActor->bHudFlag != 0) {
        pActor->nButtons &= ~2;
    }
    if (func_ov002_0206e770(1) != 0) {
        pActor->nButtons &= ~0x800;
        pActor->nButtons2 &= ~0x800;
    }
    pActor->bActionRequest = 0;
    pActor->nCommandKind = 7;
}
