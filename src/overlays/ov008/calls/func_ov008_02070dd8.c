/* func_ov008_02070dd8 -- Ov008_LayoutMissionTiles: lay out the mission
 * map's twelve tiles and its rank badge.  The three group counts (0205b958
 * 0 / 1 / 2) split the tiles; the base count of cleared missions (0205b974)
 * and, for a selected entry (+0x0) whose status field (0x28e4 + 3 * id) is
 * below 2, the total including its completion weight (+0x15) bound the
 * tiles: with an object (02050ff8) missing and the list's +0x3c set both
 * become 0.  The blink mask (+0x5c), phase (+0x5e) and tick (+0x60) are
 * reset and tags 6 / 7 / 8 disarmed.  While the base is below 12, tile i
 * (x = 0x11 + i, y 3 for the first group else 2) shows the group's idle tag
 * (0x19 / 0x1f / 0x25) -- its done tag (0x14 / 0x1a / 0x20) below the base
 * -- and tiles between base and total join the blink mask; the first tile
 * of each group also gets the group badge (0x27 / 0x29 / 0x2b idle, 0x26 /
 * 0x28 / 0x2a with a total).  A base of 12 shows the full tag 0x32 at (0x11,
 * 3) and tag 0xe at (10, 1).  The rank badge (0208f8e8 by the entry's tier,
 * 0205b988; tier 0 and a cleared blink mask when the total is 0 or equals
 * the base) goes to (0xe, 3); below 12, tier 0 puts tag 0xe at (10, 1) and
 * any other tier invokes tag 0's callback.  Codegen: the tile block is a
 * static inline helper with the tags and y as arguments (three copies); the
 * group boundary is a local computed at the top of the tile block (the
 * third count then spills); the badge tests are two separate ifs; the x
 * counter is an int stepped before the index.
 */
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef short              s16;
typedef unsigned long long u64;

#define FIELD_MISSION_STATUS 0x28e4
#define TILE_COUNT     12
#define TILE_X_FIRST   0x11
#define TAG_FULL       0x32
#define TAG_RANK       0xe

typedef struct Ov008MissionListEntry {
    u8  pad_00[2];
    u16 missionId;            /* 0x02 */
    u8  pad_04[0x15 - 4];
    u8  completionWeight;     /* 0x15 */
} Ov008MissionListEntry;

typedef struct Ov008MissionList {
    int nSelected;            /* 0x000 */
    u8  pad_004[0x3c - 4];
    int bAllQualified;        /* 0x03c */
    u8  pad_040[0x5c - 0x40];
    u16 nBlinkMask;           /* 0x05c */
    u16 nBlinkPhase;          /* 0x05e */
    u64 nBlinkTick;           /* 0x060 */
} Ov008MissionList;

typedef struct Ov008RankTags {
    u32 aTag[4];              /* badge tag per tier */
} Ov008RankTags;

extern const Ov008RankTags data_ov008_0208f8e8;
extern Ov008MissionListEntry *func_ov008_0205b670(int nIndex);           /* mission list entry */
extern int   func_ov008_02050c3c(void);                                  /* Ov008_GetCtxBlock954c */
extern int   func_ov008_02050ff8(void);                                  /* Ov008_GetCtxObject9630 */
extern int   func_ov008_0205b958(int nGroup);                            /* mission count of a group */
extern long long func_020031d4(void);                                    /* GetTick64 */
extern int   func_ov008_0205b974(void);                                  /* cleared mission count */
extern u32   func_020235d0(int nField, int nBits);                       /* GameState_GetField */
extern int   func_ov008_02055a8c(int nOwner, u32 nTag);                  /* ov008_FindActiveEntryByTag */
extern void  func_ov008_02055aec(int nOwner, int nEntry, int bArmed);    /* SetTagTrackerNodeArmed */
extern void  func_ov008_0206fe50(int nOwner, u32 nTag, short nX, short nY); /* Ov008_SetTagValueDup */
extern u8    func_ov008_0205b988(Ov008MissionListEntry *pEntry);         /* Ov008_UpdateMissionSummaryTier */
extern void *func_ov008_02055808(int nOwner, int nTag);                  /* ov008_FindEntryByTag */
extern void  func_ov008_0205589c(int nOwner, void *pEntry);              /* Ov008_TagTracker_InvokeCallback */

static inline void Ov008_SetMissionTile(Ov008MissionList *pList, int nOwner, int i, int nBase, int nTotal, u32 nTagIdle, u32 nTagDone, short nX, short nY)
{
    if (nTotal == 0) {
        func_ov008_0206fe50(nOwner, nTagIdle, nX, nY);
    } else if (i < nBase) {
        func_ov008_0206fe50(nOwner, nTagDone, nX, nY);
    } else if (i < nTotal) {
        func_ov008_0206fe50(nOwner, nTagIdle, nX, nY);
        pList->nBlinkMask |= 1 << i;
    } else {
        func_ov008_0206fe50(nOwner, nTagIdle, nX, nY);
    }
}

void func_ov008_02070dd8(Ov008MissionList *pList)
{
    Ov008RankTags tags;
    Ov008MissionListEntry *pEntry;
    int nMarkA;
    int nMarkB;
    int nMarkC;
    int nBoundary;
    int nCountC;
    int nOwner;
    int nBase;
    int nTotal;
    int nCountB;
    int i;
    int nObj;
    int nX;
    int nCountA;
    int nTier;

    pEntry = func_ov008_0205b670(pList->nSelected);
    nOwner = func_ov008_02050c3c();
    nObj = func_ov008_02050ff8();
    nCountA = func_ov008_0205b958(0);
    nCountB = func_ov008_0205b958(1);
    nCountC = func_ov008_0205b958(2);
    pList->nBlinkMask = 0;
    pList->nBlinkPhase = 0;
    pList->nBlinkTick = func_020031d4();
    nBase = func_ov008_0205b974();
    nTotal = nBase;
    if (pEntry != 0 && (int)func_020235d0(pEntry->missionId * 3 + FIELD_MISSION_STATUS, 3) < 2) {
        nTotal = nBase + pEntry->completionWeight;
    }
    if (nObj == 0 && pList->bAllQualified != 0) {
        nTotal = 0;
        nBase = nTotal;
    }
    func_ov008_02055aec(nOwner, func_ov008_02055a8c(nOwner, 6), 0);
    func_ov008_02055aec(nOwner, func_ov008_02055a8c(nOwner, 7), 0);
    func_ov008_02055aec(nOwner, func_ov008_02055a8c(nOwner, 8), 0);
    if (nBase < TILE_COUNT) {
        nBoundary = nCountA + nCountB;
        nMarkC = -1;
        nMarkB = -1;
        nMarkA = -1;
        if (nCountA > 0) {
            nMarkA = 0;
        }
        if (nCountB > 0) {
            nMarkB = nCountA;
        }
        if (nCountC > 0) {
            nMarkC = nBoundary;
        }
        nX = TILE_X_FIRST;
        for (i = 0; i < TILE_COUNT; nX++, i++) {
            if (i < nCountA) {
                Ov008_SetMissionTile(pList, nOwner, i, nBase, nTotal, 0x19, 0x14, nX, 3);
            } else if (i < nBoundary) {
                Ov008_SetMissionTile(pList, nOwner, i, nBase, nTotal, 0x1f, 0x1a, nX, 2);
            } else {
                Ov008_SetMissionTile(pList, nOwner, i, nBase, nTotal, 0x25, 0x20, nX, 2);
            }
            if (i == nMarkA) {
                if (nTotal == 0) {
                    func_ov008_0206fe50(nOwner, 0x27, nX, 4);
                }
                if (nTotal != 0) {
                    func_ov008_0206fe50(nOwner, 0x26, nX, 4);
                }
            }
            if (i == nMarkB) {
                if (nTotal == 0) {
                    func_ov008_0206fe50(nOwner, 0x29, nX, 4);
                }
                if (nTotal != 0) {
                    func_ov008_0206fe50(nOwner, 0x28, nX, 4);
                }
            }
            if (i == nMarkC) {
                if (nTotal == 0) {
                    func_ov008_0206fe50(nOwner, 0x2b, nX, 4);
                }
                if (nTotal != 0) {
                    func_ov008_0206fe50(nOwner, 0x2a, nX, 4);
                }
            }
        }
    }
    if (nBase == TILE_COUNT) {
        func_ov008_0206fe50(nOwner, TAG_FULL, TILE_X_FIRST, 3);
        func_ov008_0206fe50(nOwner, TAG_RANK, 10, 1);
    }
    tags = data_ov008_0208f8e8;
    nTier = func_ov008_0205b988(pEntry);
    if (nTotal == 0 || nTotal == nBase) {
        nTier = 0;
        pList->nBlinkMask = 0;
    }
    func_ov008_0206fe50(nOwner, tags.aTag[nTier], TAG_RANK, 3);
    if (nBase == TILE_COUNT) {
        return;
    }
    if (nTier == 0) {
        func_ov008_0206fe50(nOwner, TAG_RANK, 10, 1);
    } else {
        func_ov008_0205589c(nOwner, func_ov008_02055808(nOwner, 0));
    }
}
