/* ov022: fire one reaction request.
 *
 * A request that has waited long enough in phase 2 announces itself once: it
 * plays the actor's voice for its kind, raises that kind's bit in the request
 * mask and, for the local player's own actor, sets the actor's own announce
 * flag. From then on the request is armed, and the body below runs exactly once
 * because it raises the bit it checks.
 *
 * The kind then picks what actually happens: two of them publish a table slot,
 * several apply scaled damage or peel layers off the actor itself, and four ask
 * for the same to be spread to every other actor sharing this one's slot. The
 * spread is skipped entirely while the local player is down. Whatever the kind
 * did, modes 0xb and 0xc finish by driving a cue or a sound.
 */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

struct Actor {
    u64 nFlags;                  /* 0x0000 */
    u8 nOwner;                   /* 0x0008 */
    u8 nId;                      /* 0x0009 */
    u8 pad000a[0x5c];
    short nSlotIndex;            /* 0x0066 */
    u8 pad0068[0x3fc];
    u64 nFlags2;                 /* 0x0464 */
    u8 pad046c[0x228];
    u8 bSuppressDraw : 1;        /* 0x0694 bit 0 */
    u8 bStateOver : 1;
    u8 nSpare694 : 1;
    u8 bActionLocked : 1;        /* bit 3 */
    u8 nFlags694Top : 4;
    u8 pad0695[0x1f98];
    u8 nCue;                     /* 0x262d */
};

struct Request {
    u8 nFlags;                   /* 0x0000 */
    u8 nPhase;                   /* 0x0001 */
    u8 pad0002[0xe];
    short nKind;                 /* 0x0010 */
    u8 pad0012[2];
    int nMode;                   /* 0x0014 */
    int nParam;                  /* 0x0018 */
    u32 nKindMask;               /* 0x001c */
    u8 pad0020[0x4b0];
    int nTimer;                  /* 0x04d0 */
    u8 pad04d4[4];
    struct Actor *pActor;        /* 0x04d8 */
};

extern u8 data_0204be04;

extern int func_01fffe14(void);
extern struct Actor *func_01fffde0(int nIndex);
extern int func_02030788(void);
extern int func_020358f4(int nId, int nWhat);
extern int func_ov022_02088474(int nIndex);
extern int func_ov022_020882f8(void);
extern void func_ov022_02089fe8(int nId, int nKind, int nParam, int nFlags);
extern int func_ov022_02093a1c(int nKind);
extern int func_ov022_02093a7c(int nKind);
extern void func_ov022_02093860(struct Actor *pActor, int nDamage, int nScale);
extern void func_ov022_02093900(struct Actor *pActor, int nLayers);
extern void func_ov022_020a4490(struct Actor *pActor, int nA, int nCue);
extern void func_ov022_020aa788(struct Actor *pActor, int nKind, int nA);
extern void func_ov022_020aa824(struct Actor *pActor, int nParam, int nKind,
                                int nA);
extern int func_ov022_020ab350(struct Actor *pActor);
extern void func_ov022_020ad338(struct Actor *pActor, int nExtra, int nSel,
                                int nFlags);

void func_ov022_02093474(struct Request *pReq)
{
    struct Actor *pActor;
    struct Actor *pOther;
    int nKind;
    int bLive;
    int nSel;
    int nFlagsCopy;
    int bAllowed;
    int nScale;
    int nExtra;
    int nDamage;
    int nLayers;
    int bSpread;
    int nSlotId;
    int j;

    nKind = pReq->nKind;
    pActor = pReq->pActor;
    bLive = 0;
    if (nKind >= 2 && nKind < 0xc && pReq->nMode != 0xd) {
        bLive = 1;
    }
    if ((pReq->nFlags & 8) == 0 && pReq->nPhase == 2
        && pReq->nTimer >= 0x9000) {
        if (bLive != 0) {
            func_ov022_020a4490(pActor, 0, func_ov022_02093a7c(nKind));
            pReq->nKindMask |= 1 << func_ov022_02093a1c(pReq->nKind);
        }
        pReq->nFlags |= 8;
        if (pActor->nOwner == func_01fffe14() && bLive != 0) {
            pActor->nFlags |= 0x100000ULL;
        }
    }
    if ((pReq->nFlags & 8) == 0) {
        return;
    }
    if ((pReq->nFlags & 0x40) != 0) {
        return;
    }
    bSpread = 0;
    nDamage = 0;
    nLayers = 0;
    bAllowed = 1;
    nScale = func_020358f4(pActor->nId, 0x4a);
    nExtra = func_020358f4(pActor->nId, 0x4b);
    nFlagsCopy = pReq->nFlags;
    nSel = pReq->nKind;
    pReq->nFlags |= 0x40;
    if (pReq->nMode == 0xd) {
        nSel = 0;
    }
    pReq->nFlags |= 0x10;
    switch (nSel) {
    case 2:
        func_ov022_02093860(pActor, 0x1e, nScale);
        break;
    case 3:
        func_ov022_02093860(pActor, 0x32, nScale);
        break;
    case 4:
        bSpread = 1;
        nDamage = 0x28;
        break;
    case 5:
        func_ov022_02093900(pActor, nExtra + 1);
        break;
    case 6:
        func_ov022_02093900(pActor, nExtra + 2);
        break;
    case 7:
        nLayers = nExtra + 1;
        bSpread = 1;
        break;
    case 8:
        func_ov022_02093860(pActor, 100, nScale);
        func_ov022_02093900(pActor, 100);
        break;
    case 9:
        nDamage = 100;
        nLayers = 100;
        bSpread = 1;
        break;
    case 10:
        func_ov022_020ad338(pActor, nExtra, nSel, nFlagsCopy);
        break;
    case 11:
        if (pActor->nCue != 0) {
            pActor->nCue = pActor->nCue - 1;
        }
        break;
    default:
        func_ov022_02089fe8(pActor->nId, pReq->nKind, pReq->nParam,
                            nFlagsCopy);
        pReq->nFlags |= 0x20;
        break;
    }
    if (bSpread != 0) {
        nSlotId = pActor->nSlotIndex;
        if (func_02030788() == 0) {
            pOther = func_01fffde0(func_01fffe14());
            if (pOther->bActionLocked != 0) {
                bAllowed = 0;
            }
        } else {
            pOther = func_01fffde0(func_01fffe14());
            if (func_ov022_020ab350(pOther) != 0) {
                bAllowed = 0;
            }
        }
        j = 0;
        while (j < func_ov022_020882f8() && bAllowed != 0) {
            if (func_ov022_02088474(j) == nSlotId) {
                pOther = func_01fffde0(j);
                if ((pOther->nFlags & 0x800ULL) == 0
                    && (pOther->nFlags2 & 0x4000000000ULL) == 0
                    && (func_02030788() != 0 || pOther->bActionLocked == 0)) {
                    if (nDamage > 0) {
                        func_ov022_02093860(pOther, nDamage, nScale);
                    }
                    if (nLayers > 0) {
                        func_ov022_02093900(pOther, nLayers);
                    }
                }
            }
            j++;
        }
    }
    if (data_0204be04 != 0) {
        return;
    }
    if (bAllowed == 0) {
        return;
    }
    if (pReq->nMode == 0xb) {
        func_ov022_020aa788(pActor, pReq->nKind, -1);
        return;
    }
    if (pReq->nMode == 0xc) {
        func_ov022_020aa824(pActor, pReq->nParam, pReq->nKind, -1);
    }
}
