/* func_ov015_02081554 -- Ov015_ChestPushNearbyPlayers: for every session seat (ov022
 * 020882f8 count) with an owner slot (ov022 02088474) not yet pushed (bit in +0x72c)
 * whose current piece kind (ov002 02072754) is the chest's kind (+0x10) and whose position
 * (ov022 020881f8) lies within nRange of the chest position (+0x488): sends the player a
 * push request (ov022 02088398) of id 0xc whose offset is the unit direction chest ->
 * player scaled by 0x266, damage a tenth (0x19a / 4096) of the seat's recorded value
 * (data_0204c678 rows of 0x104 bytes, +0xe), kind 7 (def class 0x1b) or 3, strength 100 and
 * the chest as owner, then marks the seat's bit. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov015PushRequest {
    int  nId;                 /* 0x00 */
    VecFx32 vecOffset;        /* 0x04 */
    int  nDamage;             /* 0x10 */
    int  nKind;               /* 0x14 */
    u8   nStrength;           /* 0x18 */
    u8   pad_19[3];
    void *pOwner;             /* 0x1c */
    u8   pad_20[8];
} Ov015PushRequest;

typedef struct Ov015MissionMember {
    u8   pad_00[0xe];
    u16  wRecordedValue;      /* 0x0e */
    u8   pad_10[0x104 - 0x10];
} Ov015MissionMember;

typedef struct Ov015ChestDef {
    u8   pad_00[0x4c];
    u16  nClass;              /* 0x4c: 0x1b / 0x1c */
} Ov015ChestDef;

typedef struct Ov015Chest {
    u8   pad_000[8];
    Ov015ChestDef *pDef;      /* 0x008 */
    u8   pad_00c[4];
    u8   nKind;               /* 0x010 */
    u8   pad_011[0x488 - 0x11];
    VecFx32 position;         /* 0x488 */
    u8   pad_494[0x72c - 0x494];
    u8   nPushedMask;         /* 0x72c */
} Ov015Chest;

extern Ov015MissionMember data_0204c678[];

extern int  func_ov022_020882f8(void);                                    /* seat count */
extern int  func_ov022_02088474(int nSeat);                               /* seat -> owner slot */
extern int  func_ov002_02072754(void);                                    /* current piece kind */
extern VecFx32 *func_ov022_020881f8(int nSeat);                           /* where the seat is */
extern int  func_01ff8e94(const VecFx32 *pA, const VecFx32 *pB);          /* VEC_Distance */
extern void VEC_Subtract(const VecFx32 *pA, const VecFx32 *pB, VecFx32 *pOut);
extern void func_01ff8d18(VecFx32 *pVec, VecFx32 *pOut);                  /* VEC_Normalize */
extern void func_01ffa724(int nScale, const VecFx32 *pVec, VecFx32 *pOut); /* ScaleVec3Fx12 */
extern int  func_ov022_02088398(int nSeat, Ov015PushRequest *pRequest);   /* send a request to the seat's player */

void func_ov015_02081554(Ov015Chest *pChest, int nRange)
{
    int i;
    Ov015ChestDef *pDef;
    Ov015PushRequest request;
    VecFx32 direction;

    pDef = pChest->pDef;
    for (i = 0; i < func_ov022_020882f8(); i++) {
        if (func_ov022_02088474(i) >= 0 && (pChest->nPushedMask & (1 << i)) == 0) {
            func_ov022_02088474(i);
            if (pChest->nKind == func_ov002_02072754()) {
                if (nRange >= func_01ff8e94(&pChest->position, func_ov022_020881f8(i))) {
                    VEC_Subtract(func_ov022_020881f8(i), &pChest->position, &direction);
                    func_01ff8d18(&direction, &direction);
                    func_01ffa724(0x266, &direction, &request.vecOffset);
                    request.nDamage = (data_0204c678[i].wRecordedValue * 0x19a) >> 12;
                    request.nKind = (pDef->nClass == 0x1b) ? 7 : 3;
                    request.nStrength = 100;
                    request.nId = 0xc;
                    request.pOwner = pChest;
                    func_ov022_02088398(i, &request);
                    pChest->nPushedMask |= 1 << i;
                }
            }
        }
    }
}
