/* func_ov008_020745c4 -- Ov008_StartSelectedMission: commit the mission named by
 * the context.  Records its id (data_0204c23c) when it is listed, fills the game
 * mode record (mission entry word, timer 0, sub 0x13, flags 0xf or 7 in a
 * session, mission kind byte) and copies the entry's seven threshold words, sets
 * the mission's unlock flag (0x3bc9 + slot) if not yet set, plays the start cue
 * (enabling the sound layer when the page has not yet) and, depending on the
 * ctx object 95c0, either targets slot 0 and sets flag 0x200a or targets no
 * slot with 0x5dc.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov008MissionListEntry {
    u16 nWord;                /* 0x00 */
    u8  pad_02[2];
    u16 nSlot;                /* 0x04 */
    u8  pad_06[0x18 - 0x06];
    int nKind;                /* 0x18 */
    u8  pad_1c[4];
    u32 aThreshold[7];        /* 0x20 */
} Ov008MissionListEntry;

typedef struct GameplayThresholdSnapshot {
    u32 words[7];
} GameplayThresholdSnapshot;

typedef struct GameMode {
    u8  nFlags;               /* 0x00 */
    u8  nSub;                 /* 0x01 */
    u16 nWord;                /* 0x02 */
    u16 nTimer;               /* 0x04 */
    u8  nKind;                /* 0x06 */
} GameMode;

typedef struct Ov008PageB {
    u8  pad_000[0x150];
    int bSoundReady;          /* 0x150 */
} Ov008PageB;

#define FLAG_SLOT_BASE 0x3bc9
#define FLAG_TARGET_ANY 0x5dc
#define FLAG_TARGET_SLOT0 0x200a
#define MODE_SUB_MISSION 0x13

extern u16 data_0204c23c;                                  /* current mission id */
extern GameMode data_0204c240;
extern GameplayThresholdSnapshot data_0204c254;

extern Ov008PageB *func_ov008_02050cec(void);              /* Ov008_GetPageB */
extern u32  func_ov008_020511e0(void);                     /* Ov008_GetCtxField967c */
extern Ov008MissionListEntry *func_ov008_0205b6e8(u32 nMissionId);
extern int  func_02030670(void);                           /* Session_IsActive */
extern int  func_02023588(int nFlag);                      /* GameState_IsFlagSet */
extern void func_020235a8(int nFlag);                      /* GameState_SetFlag */
extern void func_ov008_02050f04(int bEnable);
extern void func_02033fb4(int nA, int nB);                 /* StampByteAndInvokeSubStructAt */
extern void func_02033b78(int nKind, int nSound);          /* PlaySound */
extern int  func_ov008_02050fc8(void);                     /* Ov008_GetCtxObject95c0 */
extern void func_ov008_02050970(int nEntry, int nTarget);  /* Ov008_SetTargetSlot */

void func_ov008_020745c4(void)
{
    Ov008PageB *pPage = func_ov008_02050cec();
    Ov008MissionListEntry *pEntry;

    pEntry = func_ov008_0205b6e8(func_ov008_020511e0());
    if (pEntry != 0) {
        data_0204c23c = func_ov008_020511e0();
    }
    data_0204c240.nWord = pEntry->nWord;
    data_0204c240.nTimer = 0;
    data_0204c240.nSub = MODE_SUB_MISSION;
    data_0204c240.nFlags = func_02030670() != 0 ? 7 : 0xf;
    data_0204c240.nKind = pEntry->nKind;
    data_0204c254 = *(GameplayThresholdSnapshot *)pEntry->aThreshold;
    if (func_02023588(pEntry->nSlot + FLAG_SLOT_BASE) == 0) {
        func_020235a8(pEntry->nSlot + FLAG_SLOT_BASE);
    }
    if (pPage->bSoundReady == 0) {
        func_ov008_02050f04(0);
        func_02033fb4(1, 4);
    } else {
        func_02033b78(0, 1);
    }
    if (func_ov008_02050fc8() != 2) {
        func_ov008_02050970(-1, FLAG_TARGET_ANY);
        return;
    }
    func_ov008_02050970(0, -1);
    func_020235a8(FLAG_TARGET_SLOT0);
}
