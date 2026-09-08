typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

struct VecFx32 {
    int x;
    int y;
    int z;
};

struct Node {
    u8 pad00[0x82];
    u16 nAngleReplay;                /* 0x82 */
};

struct Actor {
    u8 pad000[0x20];
    struct Node *pNode;              /* 0x020 */
    u8 pad024[0x454];
    short nAngleBias;                /* 0x478 */
    s8 nField47a;                    /* 0x47a */
    s8 nField47b;                    /* 0x47b */
    u8 pad47c[0x60];
    s8 nLatchedKind;                 /* 0x4dc */
    u8 pad4dd[1];
    u16 nLatchedArg;                 /* 0x4de */
    u16 nLatchedArg2;                /* 0x4e0 */
    u8 pad4e2[0xe];
    u8 nRefKind;                     /* 0x4f0 */
    u8 nRefId;                       /* 0x4f1 */
    u8 nRefIndex;                    /* 0x4f2 */
    u8 pad4f3[1];
    int nRefMode;                    /* 0x4f4 */
    u8 pad4f8[0x19c];
    u8 nSpare694 : 3;                /* 0x694 bits 0-2 */
    u8 bActionLocked : 1;              /*       bit 3 */
    u8 nSpare694Top : 4;             /*       bits 4-7 */
    u8 pad695[0x27];
    int nHitReaction;                /* 0x6bc */
    u8 pad6c0[0x20b0];
    s8 nKnockdownKind;               /* 0x2770 */
    u8 pad2771[0x342];
    u8 nRumbleLevel;                 /* 0x2ab3 */
    u8 nRumbleState;                 /* 0x2ab4 */
    u8 nRumbleRequest;               /* 0x2ab5 */
    u8 pad2ab6[4];
    short nAreaFrame;                /* 0x2aba */
};

/* One 0x30-byte slot of the status packet the gate receives each frame. */
struct StatusRecord {
    unsigned long long nStamp;       /* 0x00 */
    struct VecFx32 vecAt;            /* 0x08 */
    int nField14;                    /* 0x14 */
    u16 nField18;                    /* 0x18 */
    u16 nAngleReplay;                /* 0x1a */
    short nHitReaction;              /* 0x1c */
    short nAngleBias;                /* 0x1e */
    u16 nField20;                    /* 0x20 */
    short nAreaFrame;                /* 0x22 */
    u16 nRefKind : 2;                /* 0x24 bits 0-1 */
    u16 nRefMode : 1;                /*      bit 2 */
    u16 nRefIndex : 5;               /*      bits 3-7 */
    u16 nRefId : 8;                  /*      bits 8-15 */
    u16 nRumbleLevel : 4;            /* 0x26 bits 0-3 */
    u16 nRumbleRequest : 5;          /*      bits 4-8 */
    u16 nRumbleState : 3;            /*      bits 9-11 */
    u16 nKnockdownKind : 4;          /*      bits 12-15 */
    u32 nLatchedKind : 4;            /* 0x28 bits 0-3 */
    u32 nLatchedArg : 10;            /*      bits 4-13 */
    u32 nLatchedArg2 : 10;           /*      bits 14-23 */
    u32 bActionLocked : 1;             /*      bit 24 */
    u32 nOwner : 4;                  /*      bits 25-28 */
    u32 nField66 : 3;                /*      bits 29-31 */
    s8 nField47a : 4;                /* 0x2c bits 0-3 */
    s8 nField47b : 4;                /*      bits 4-7 */
    u8 pad2d[3];
};

#define SLOT_COUNT 4

extern int func_ov022_020882f8(void);
extern struct Actor *func_01fffde0(int nOwner);
extern unsigned long long func_ov022_02088314(int nOwner);
extern struct VecFx32 *func_ov022_020881f8(int nOwner);
extern int func_ov022_02088370(int nOwner);
extern u16 func_ov022_02088254(int nOwner);
extern u16 func_ov022_020882e0(int nOwner);
extern int func_ov022_02088474(int nOwner);
extern int func_02031258(int nGate, u16 *pData, u16 nSize);

void func_ov022_0208981c(void)
{
    struct StatusRecord aRecords[SLOT_COUNT];
    struct StatusRecord *pRecord;
    struct Actor *pActor;
    int nOwner;

    pRecord = aRecords;
    nOwner = 0;
    if (func_ov022_020882f8() > 0) {
        do {
            pActor = func_01fffde0(nOwner);
            pRecord->nStamp = func_ov022_02088314(nOwner);
            pRecord->vecAt = *func_ov022_020881f8(nOwner);
            pRecord->nField14 = func_ov022_02088370(nOwner);
            pRecord->nField18 = func_ov022_02088254(nOwner);
            pRecord->nAngleReplay = pActor->pNode->nAngleReplay;
            pRecord->nHitReaction = (short)pActor->nHitReaction;
            pRecord->nAngleBias = pActor->nAngleBias;
            pRecord->nField20 = func_ov022_020882e0(nOwner);
            pRecord->nAreaFrame = pActor->nAreaFrame;
            pRecord->nRefKind = pActor->nRefKind;
            pRecord->nRefIndex = pActor->nRefIndex;
            pRecord->nRefId = pActor->nRefId;
            pRecord->nRefMode = pActor->nRefMode;
            pRecord->nRumbleLevel = pActor->nRumbleLevel;
            pRecord->nRumbleRequest = pActor->nRumbleRequest;
            pRecord->nRumbleState = pActor->nRumbleState;
            pRecord->nKnockdownKind = pActor->nKnockdownKind;
            pRecord->nOwner = nOwner;
            pRecord->nField66 = func_ov022_02088474(nOwner);
            pRecord->nLatchedArg = pActor->nLatchedArg;
            pRecord->nLatchedKind = pActor->nLatchedKind;
            pRecord->nLatchedArg2 = pActor->nLatchedArg2;
            pRecord->nField47a = pActor->nField47a;
            pRecord->nField47b = pActor->nField47b;
            if (pRecord->nField20 != 0) {
                pRecord->bActionLocked = pActor->bActionLocked;
            }
            nOwner = nOwner + 1;
            pRecord = pRecord + 1;
        } while (nOwner < func_ov022_020882f8());
    }
    func_02031258(0, (u16 *)aRecords, sizeof(aRecords));
}
