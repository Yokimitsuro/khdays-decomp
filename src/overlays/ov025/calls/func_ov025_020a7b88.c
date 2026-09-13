/* func_ov025_020a7b88 -- Ov008_InitMissionListProgress: count the mission
 * list's dots and start its animations.  Every entry that is special (+0xc) or
 * flagged (+0x14 bit 1) counts one dot (+0x56); those whose rank field
 * (0x28e4 + 3 * id, 3 bits) is at least 2 count one finished dot (+0x55); an
 * entry that is neither special nor flagged clears the all-qualified word
 * (+0x3c).  Touch (+0x38) is enabled when 0205b690 allows it and every
 * special / flagged entry is finished.  The node tutorial fires once and
 * drives the animation words (+0x68 running, +0x6c phase 1 while running,
 * +0x6e step 0, +0x70 start tick); with neither context object 9634 / 9630
 * nor an animation running, a pending mission kind raises the prompt flag
 * (+0x78) and starts the animation the same way.  The blink words (+0x5c /
 * +0x5e) are reset with their tick (+0x60), and GameState field 0 (9 bits)
 * at 0x47 or more runs ov008_helper_6fe4c.
 */
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

#define FIELD_RANK_BASE 0x28e4
#define FIELD_BITS      3
#define ENTRY_FLAGGED   2
#define RANK_DONE       2
#define STORY_FIELD_BITS 9
#define STORY_THRESHOLD 0x47

typedef struct Ov008MissionListEntry {
    u8  pad_00[2];
    u16 missionId;            /* 0x02 */
    u8  pad_04[8];
    u8  bSpecial;             /* 0x0c */
    u8  pad_0d[7];
    u8  nFlags;               /* 0x14 */
} Ov008MissionListEntry;

typedef struct Ov008MissionList {
    u8  pad_00[0x38];
    int bTouchEnabled;        /* 0x38 */
    int bAllQualified;        /* 0x3c */
    u8  pad_40[0x55 - 0x40];
    u8  nDotsDone;            /* 0x55 */
    u8  nDots;                /* 0x56 */
    u8  pad_57[0x5c - 0x57];
    u16 nBlinkA;              /* 0x5c */
    u16 nBlinkB;              /* 0x5e */
    u64 nBlinkTick;           /* 0x60 */
    int bAnimating;           /* 0x68 */
    u16 nAnimPhase;           /* 0x6c */
    u16 nAnimStep;            /* 0x6e */
    u64 nAnimTick;            /* 0x70 */
    int bPendingPrompt;       /* 0x78 */
} Ov008MissionList;

extern int  func_ov025_0208dbfc(void);                                    /* touch allowed */
extern Ov008MissionListEntry *func_ov025_0208dbbc(Ov008MissionListEntry *pEntry); /* Ov008_GetNextMissionEntry */
extern u32  func_020235d0(int nField, int nBits);                         /* GameState_GetField */
extern int  func_ov025_020a4fc0(void);                                    /* Ov008_FireNodeTutorialOnce */
extern long long func_020031d4(void);                                     /* GetTick64 */
extern int  func_ov025_02084e38(void);                                    /* Ov008_GetCtxObject9634 */
extern int  func_ov025_02084e08(void);                                    /* Ov008_GetCtxObject9630 */
extern int  func_ov025_020a5028(void);                                    /* Ov008_AnyMissionKindPending */
extern void func_ov025_020a53f0(void);                                    /* ov008_helper_6fe4c */

void func_ov025_020a7b88(Ov008MissionList *pList)
{
    int bTouch;
    int nFlagged;
    int nSpecial;
    int nFlaggedDone;
    int nSpecialDone;
    Ov008MissionListEntry *pEntry;
    int bDone;

    bTouch = func_ov025_0208dbfc();
    nFlagged = 0;
    pList->nDots = 0;
    pList->nDotsDone = 0;
    nFlaggedDone = 0;
    nSpecial = 0;
    nSpecialDone = 0;
    pList->bAllQualified = 1;
    for (pEntry = func_ov025_0208dbbc(0); pEntry != 0; pEntry = func_ov025_0208dbbc(pEntry)) {
        if (pEntry->bSpecial == 0 && (pEntry->nFlags & ENTRY_FLAGGED) == 0) {
            pList->bAllQualified = 0;
        }
        if (pEntry->bSpecial != 0) {
            nSpecial++;
        }
        if (pEntry->nFlags & ENTRY_FLAGGED) {
            nFlagged++;
        }
        bDone = func_020235d0(pEntry->missionId * 3 + FIELD_RANK_BASE, FIELD_BITS) >= RANK_DONE;
        if (bDone) {
            if (pEntry->bSpecial != 0) {
                nSpecialDone++;
            }
            if (pEntry->nFlags & ENTRY_FLAGGED) {
                nFlaggedDone++;
            }
        }
    }
    pList->nDots = nSpecial + nFlagged;
    pList->nDotsDone = nSpecialDone + nFlaggedDone;
    pList->bTouchEnabled = 0;
    if (bTouch != 0) {
        if (nSpecialDone >= nSpecial && nFlaggedDone >= nFlagged) {
            pList->bTouchEnabled = 1;
        }
    }
    pList->bAnimating = func_ov025_020a4fc0();
    pList->nAnimStep = 0;
    pList->nAnimTick = func_020031d4();
    pList->nAnimPhase = 0;
    if (pList->bAnimating != 0) {
        pList->nAnimPhase = 1;
    }
    if (func_ov025_02084e38() == 0 && func_ov025_02084e08() == 0 && pList->bAnimating == 0
        && func_ov025_020a5028() != 0) {
        pList->bPendingPrompt = 1;
        pList->bAnimating = 1;
        pList->nAnimStep = 0;
        pList->nAnimTick = func_020031d4();
        pList->nAnimPhase = 0;
        if (pList->bAnimating != 0) {
            pList->nAnimPhase = 1;
        }
    }
    pList->nBlinkA = 0;
    pList->nBlinkB = 0;
    pList->nBlinkTick = func_020031d4();
    if (func_020235d0(0, STORY_FIELD_BITS) >= STORY_THRESHOLD) {
        func_ov025_020a53f0();
    }
}
