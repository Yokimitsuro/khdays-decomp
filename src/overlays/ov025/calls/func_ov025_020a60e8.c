/* func_ov025_020a60e8 -- Ov008_LayoutMissionDots: lay out the mission list's
 * dot row.  Disarms the active dot (tag 0xb); the first "open" dot index is
 * nDone + 1 when the selected mission is flagged (entry byte +0xc or bit 1 of
 * +0x14) and not yet cleared (status field < 2), else none (-1).  Then for each
 * of the nDots dots (x = 2 + 2 * i): done dots use tag 0x3c, the open one the
 * active tag 0xb, the rest tag 0x41, all at y = 2.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef short          s16;
typedef unsigned int   u32;

#define FIELD_MISSION_STATUS 0x28e4
#define TAG_DOT_ACTIVE 0xb
#define TAG_DOT_DONE   0x3c
#define TAG_DOT_TODO   0x41
#define DOT_Y     2
#define DOT_STEP  2

typedef struct Ov008MissionListEntry {
    u8  pad_00[2];
    u16 missionId;            /* 0x02 */
    u8  pad_04[8];
    u8  bSpecial;             /* 0x0c */
    u8  pad_0d[7];
    u8  nFlags;               /* 0x14: bit 1 = flagged */
} Ov008MissionListEntry;

typedef struct Ov008MissionList {
    int nSelected;            /* 0x000 */
    u8  pad_004[0x55 - 0x04];
    u8  nDotsDone;            /* 0x055 */
    u8  nDots;                /* 0x056 */
} Ov008MissionList;

extern int  func_ov025_02084a64(void);                                    /* Ov008_GetCtxBlock954c */
extern int  func_ov025_0208969c(int nOwner, u32 nTag);                    /* ov008_FindActiveEntryByTag */
extern void func_ov025_020896fc(int nOwner, int nEntry, int bArmed);      /* SetTagTrackerNodeArmed */
extern Ov008MissionListEntry *func_ov025_0208dbdc(int nIndex);
extern u32  func_020235d0(int nField, int nBits);                         /* GameState_GetField */
extern void func_ov025_020a53f4(int nOwner, u32 nTag, short nX, short nY); /* Ov008_SetTagValueDup */
extern void func_ov025_020a543c(int nOwner, u32 nTag, short nX, short nY); /* Ov008_SetActiveTagValueAndFlag2 */

static inline int Ov008_IsMissionCleared(Ov008MissionListEntry *pEntry)
{
    return func_020235d0(pEntry->missionId * 3 + FIELD_MISSION_STATUS, 3) >= 2;
}

void func_ov025_020a60e8(Ov008MissionList *pList)
{
    int i;
    int nX;
    int nOpen;
    int nOwner;
    Ov008MissionListEntry *pEntry;

    nOwner = func_ov025_02084a64();
    func_ov025_020896fc(nOwner, func_ov025_0208969c(nOwner, TAG_DOT_ACTIVE), 0);
    nOpen = -1;
    if (pList->nSelected >= 0) {
        pEntry = func_ov025_0208dbdc(pList->nSelected);
        if (pEntry->bSpecial != 0 || (pEntry->nFlags & 2) != 0) {
            if (!Ov008_IsMissionCleared(pEntry)) {
                nOpen = pList->nDotsDone + 1;
            }
        }
    }
    nX = DOT_STEP;
    for (i = 0; i < pList->nDots; i++, nX += DOT_STEP) {
        if (i < pList->nDotsDone) {
            func_ov025_020a53f4(nOwner, TAG_DOT_DONE, nX, DOT_Y);
        } else if (i < nOpen) {
            func_ov025_020a543c(nOwner, TAG_DOT_ACTIVE, nX, DOT_Y);
        } else {
            func_ov025_020a53f4(nOwner, TAG_DOT_TODO, nX, DOT_Y);
        }
    }
}
