/* Ov022_StepChargeEntries -- advance the actor's three charge entries a frame
 * and post its position.
 *
 * Entry 2 animates only in menu state 3 and entry 0 only in menu state 7;
 * otherwise their five tracks are reset to zero. Entry 1 animates while flag-2
 * bit 49 or 50 is set, after a reset to 1 (bit 50) or 1/0 (bit 49 only); when
 * its tracks report done under bit 50 on the local machine the charge's
 * released bit is dropped. With neither bit its tracks are reset. Finally the
 * actor's aim raised by its reach is posted with its id and menu state.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long long u64;

struct VecFx32 {
    int x;
    int y;
    int z;
};

/* Ov022ChargeEntry */
struct ChargeEntry {
    u16 nTrackFlags;                 /* 0x000 head of the five tracks */
    u8 pad002[0x106];
};

/* Ov022Charge */
struct Charge {
    u8 pad00[0xc];
    u8 bReleased;                    /* 0x0c */
    u8 pad0d[0xf];
    struct ChargeEntry aEntries[3];  /* 0x1c */
};

/* Ov022Actor */
struct Actor {
    u8 pad0000[9];
    u8 nId;                          /* 0x0009 */
    u8 pad000a[0x45a];
    u64 nFlags2;                     /* 0x0464 */
    u8 pad046c[0x20];
    struct VecFx32 vecAim;           /* 0x048c */
    u8 pad0498[0x2220];
    int nReach;                      /* 0x26b8 */
    u8 pad26bc[0xb4];
    struct Charge charge;            /* 0x2770 */
    u8 pad2aa4[0x14];
    u8 nMenuState;                   /* 0x2ab8 */
};

#define FLAG2_BIT49 (1ULL << 49)
#define FLAG2_BIT50 (1ULL << 50)
#define MENU_STATE_3 3
#define MENU_STATE_7 7

extern int func_0202a818(u16 *pAnim, int nDelta);
extern void func_ov022_0209b0c0(struct Actor *pActor, int nEntry, int nValue);
extern void func_ov022_0209b078(struct Actor *pActor, int nEntry, int nValue);
extern int func_02030788(void);
extern void func_ov022_020b2020(int nKind, int nId, int nState, struct VecFx32 *pPos);

void func_ov022_0209aefc(struct Actor *pActor, int nDelta)
{
    struct VecFx32 vecPos;
    struct Charge *pCharge;

    pCharge = &pActor->charge;
    if (pActor->nMenuState == MENU_STATE_3) {
        func_0202a818(&pCharge->aEntries[2].nTrackFlags, nDelta);
    } else {
        func_ov022_0209b0c0(pActor, 2, 0);
    }
    if ((pActor->nFlags2 & FLAG2_BIT49) != 0 || (pActor->nFlags2 & FLAG2_BIT50) != 0) {
        if ((pActor->nFlags2 & FLAG2_BIT50) != 0) {
            func_ov022_0209b078(pActor, 1, 1);
        } else if ((pActor->nFlags2 & FLAG2_BIT49) != 0) {
            func_ov022_0209b078(pActor, 1, 0);
        }
        if (func_0202a818(&pCharge->aEntries[1].nTrackFlags, nDelta) != 0
            && (pActor->nFlags2 & FLAG2_BIT50) != 0 && func_02030788() == 0) {
            pCharge->bReleased &= ~1;
        }
    } else {
        func_ov022_0209b0c0(pActor, 1, 0);
    }
    if (pActor->nMenuState == MENU_STATE_7) {
        func_0202a818(&pCharge->aEntries[0].nTrackFlags, nDelta);
    } else {
        func_ov022_0209b0c0(pActor, 0, 0);
    }
    vecPos = pActor->vecAim;
    vecPos.y += pActor->nReach;
    func_ov022_020b2020(1, pActor->nId, pActor->nMenuState, &vecPos);
}
