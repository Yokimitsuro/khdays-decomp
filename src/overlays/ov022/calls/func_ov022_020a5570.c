/* Ov022_RunComboContacts -- run the combo record's contact slots for the
 * frame and keep the strongest contact.
 *
 * A record whose flag 2 is up uses its own hit-id list; otherwise each slot
 * names one of the record's lists or carries its own. A live sub-object is told the
 * record's hold. Each slot counts as full when its bit says so, or when slot
 * rule 0x3a holds and the actor is at full health; the record's mode picks
 * the handler that tests it (0, 1, or 2 which also answers the result). The
 * contact each handler leaves is kept when its state is 1..3, or 4 while the
 * contact kind is 1 or 4; the kept contact is written back at the end.
 */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

/* Ov022SweepContact */
struct SweepContact {
    int nResult;                 /* 0x00 */
    int nKind;                   /* 0x04 */
    u8 nState;                   /* 0x08 */
    u8 pad09[0xab];
};

/* Ov022ComboSlot: one 0x48-byte contact slot of a record */
struct ComboSlot {
    u8 pad00[0x14];
    u8 bFull : 1;                /* 0x14 bit 0 */
    u8 nRest14 : 7;
    s8 nHitIdList;               /* 0x15 index into the record's hit-id lists, or own */
    u8 pad16[0x22];
    short aHitIds[8];            /* 0x38 the slot's own hit-id list */
};

/* Ov022ComboRecord */
struct ComboRecord {
    u8 pad00[2];
    u8 nMode;                    /* 0x02 which contact handler runs */
    u8 pad03[0x15];
    int nHold;                   /* 0x18 */
    u8 pad1c[0x10];
    u32 nFlags2c;                /* 0x2c bit 1: one hit-id list for all slots */
    short nSlotCount;            /* 0x30 */
    u8 pad32[2];
    struct ComboSlot *pSlots;    /* 0x34 */
    u8 pad38[6];
    short aHitIdLists[1][8];     /* 0x3e */
};

/* Ov022ComboLock */
struct ComboLock {
    u8 pad00[0x14];
    struct ComboRecord *pRecord; /* 0x14 */
};

/* Ov022ActorSub */
struct ActorSub {
    u8 pad00[0x54];
    int nHold;                   /* 0x54 */
};

/* Ov022Actor */
struct Actor {
    u8 pad0000[9];
    u8 nId;                      /* 0x0009 */
    u8 pad000a[8];
    u16 nHp;                     /* 0x0012 */
    u8 pad0014[2];
    u16 nHpMax;                  /* 0x0016 */
    u8 pad0018[0x4d4];
    struct ActorSub *pSub;       /* 0x04ec */
    u8 pad04f0[0x890];
    struct ComboLock *pComboLock;/* 0x0d80 */
    u8 pad0d84[0x1938];
    struct SweepContact contact; /* 0x26bc */
};

#define RECORD_SHARED_IDS 0x2
#define RULE_FULL_HEALTH 0x3a
#define CONTACT_MODE_0 0
#define CONTACT_MODE_1 1
#define CONTACT_MODE_2 2

extern int func_020358f4(int nId, int nRule);
extern void func_ov022_020a5768(struct Actor *pActor, struct ComboSlot *pSlot, short *pHitIds, int bFull);
extern void func_ov022_020a59b8(struct Actor *pActor, struct ComboSlot *pSlot, short *pHitIds, int bFull);
extern int func_ov022_020a5d18(struct Actor *pActor, struct ComboSlot *pSlot, int bFull);

int func_ov022_020a5570(struct Actor *pActor)
{
    struct SweepContact kept;
    int nRet;
    struct ComboRecord *pRecord;
    struct SweepContact *pContact;
    int bFull;
    short *pHitIds;
    int nSlot;
    struct ComboSlot *pSlot;

    pRecord = pActor->pComboLock->pRecord;
    pContact = &pActor->contact;
    nRet = 0;
    if ((pRecord->nFlags2c & RECORD_SHARED_IDS) != 0) {
        pHitIds = pRecord->aHitIdLists[0];
    }
    if (pActor->pSub != 0 && pRecord->nHold > 0) {
        pActor->pSub->nHold = pRecord->nHold;
    }
    kept.nResult = 0;
    kept.nState = 0;
    for (nSlot = 0; nSlot < pRecord->nSlotCount; nSlot++) {
        pSlot = &pRecord->pSlots[nSlot];
        bFull = pSlot->bFull;
        if (func_020358f4(pActor->nId, RULE_FULL_HEALTH) != 0 && pActor->nHp == pActor->nHpMax) {
            bFull = 1;
        }
        if ((pRecord->nFlags2c & RECORD_SHARED_IDS) == 0) {
            if (pSlot->nHitIdList < 0) {
                pHitIds = pSlot->aHitIds;
            } else {
                pHitIds = pRecord->aHitIdLists[pSlot->nHitIdList];
            }
        }
        pContact->nResult = 0;
        pContact->nState = 0;
        switch (pRecord->nMode) {
        case CONTACT_MODE_0:
            func_ov022_020a5768(pActor, pSlot, pHitIds, bFull);
            break;
        case CONTACT_MODE_1:
            func_ov022_020a59b8(pActor, pSlot, pHitIds, bFull);
            break;
        case CONTACT_MODE_2:
            nRet = func_ov022_020a5d18(pActor, pSlot, bFull);
            break;
        }
        switch (pContact->nState) {
        case 1:
        case 2:
        case 3:
            kept = *pContact;
            break;
        case 4:
            if (pActor->contact.nKind == 1 || pActor->contact.nKind == 4) {
                kept = *pContact;
            }
            break;
        }
    }
    pActor->contact = kept;
    return nRet;
}
