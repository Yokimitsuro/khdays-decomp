/* Ov022_StepFollowSlot -- keep an actor's follow slot in step with the
 * partner it trails.
 *
 * The slot is the actor's own player slot entry; a stalled slot (state 3) is
 * put back to 1 first. An actor referencing an item gets a half unit of extra
 * reach. Beyond the reach the slot is given a one-unit wait once (while the
 * item reference holds) and stalls when that wait has run out. Within reach
 * the aim is copied into the slot and its wait flag dropped, unless the
 * partner is further than the inner reach with button bit 6 down, the
 * partner carries flag-2 bit 7 without the actor matching it with flag bit
 * 36, or the actor carries flag bit 14 or 26; any of those stalls the slot.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

/* Ov022SlotDesc: the reach pair of a player slot */
struct SlotDesc {
    u8 pad00[0x18];
    int nReachOuter;             /* 0x18 */
    int nReachInner;             /* 0x1c */
};

/* Ov022PlayerSlot */
struct PlayerSlot {
    int nState;                  /* 0x00 1 following, 3 stalled */
    u32 nFlags;                  /* 0x04 bit 7: waiting */
    int nField08;                /* 0x08 */
    u8 pad0c[0xc];
    int nWait;                   /* 0x18 */
    u8 pad1c[4];
    VecFx32 vecPos;              /* 0x20 */
    u8 pad2c[0x18];
    struct SlotDesc *pDesc;      /* 0x44 */
};

/* Ov022Actor */
struct Actor {
    u64 nFlags;                  /* 0x0000 */
    u8 pad0008[1];
    u8 nId;                      /* 0x0009 */
    u8 pad000a[0x10];
    u16 nButtons2;               /* 0x001a */
    u8 pad001c[0x448];
    u64 nFlags2;                 /* 0x0464 */
    u8 pad046c[0x20];
    VecFx32 vecAim;              /* 0x048c */
    u8 pad0498[0x58];
    u8 nRefKind;                 /* 0x04f0 */
    u8 pad04f1[0xf];
    void *pRefItem;              /* 0x0500 */
};

#define FLAG_BIT14 (1ULL << 14)
#define FLAG_BIT26 (1ULL << 26)
#define FLAG_BIT36 (1ULL << 36)
#define FLAG2_BIT7 (1ULL << 7)
#define BUTTON2_BIT6 0x40
#define SLOT_FOLLOWING 1
#define SLOT_STALLED 3
#define SLOT_WAITING 0x80
#define REF_ITEM 1
#define ITEM_SLACK 0x2000
#define SLOT_WAIT 0x1000

extern int func_01ff8e94(VecFx32 *pA, VecFx32 *pB);         /* VEC_Distance */
extern struct PlayerSlot *func_020358a4(int nSlot);

void func_ov022_020aed60(struct Actor *pActor, struct Actor *pPartner)
{
    int nDist;
    struct PlayerSlot *pSlot;
    int nSlack;

    nDist = func_01ff8e94(&pPartner->vecAim, &pActor->vecAim);
    pSlot = func_020358a4((u8)(pActor->nId - 1));
    nSlack = 0;
    if (pSlot->nState == SLOT_STALLED) {
        pSlot->nState = SLOT_FOLLOWING;
    }
    if (pActor->nRefKind == REF_ITEM && pActor->pRefItem != 0) {
        nSlack = ITEM_SLACK;
    }
    if (pSlot->pDesc->nReachOuter + nSlack < nDist) {
        if (pActor->nRefKind == REF_ITEM && pActor->pRefItem != 0
            && (pSlot->nFlags & SLOT_WAITING) == 0) {
            pSlot->nWait = SLOT_WAIT;
            pSlot->nFlags |= SLOT_WAITING;
        }
        if (pSlot->nWait <= 0) {
            pSlot->nState = SLOT_STALLED;
        }
    } else {
        if ((pSlot->pDesc->nReachInner < nDist && (pActor->nButtons2 & BUTTON2_BIT6) != 0)
            || ((pPartner->nFlags2 & FLAG2_BIT7) != 0
                && ((pActor->nFlags2 & FLAG2_BIT7) == 0 || (pActor->nFlags & FLAG_BIT36) == 0))
            || (pActor->nFlags & FLAG_BIT14) != 0 || (pActor->nFlags & FLAG_BIT26) != 0) {
            pSlot->nState = SLOT_STALLED;
        } else {
            pActor->nButtons2 = 0;
            pSlot->nField08 = 0;
            pSlot->nFlags &= ~SLOT_WAITING;
            pSlot->vecPos = pActor->vecAim;
        }
    }
}
