/* Builds the missions' list node of one record of UI/cm/msl_&.msi.z: allocates the 0x58-byte node,
 * zeroes it, copies the record's fields at their widths (several u16/u8 values widened into words,
 * two u16 truncated to bytes; bHidden is the record's +0xc == 1), then reads the record's four
 * texts out of pTexts with Ov025_DupWideString, threading the cursor: the name, the briefing, the
 * objective and the format. */

#include "nitro/types.h"

/* A record of the missions' list, led by its size. */
typedef struct Ov008MissionListRecord {
    u16 nSize;                /* 0x00 */
    u16 nFileNumber;          /* 0x02: the mission's file (mi/mi/<number>), the room key */
    u16 nMissionNumber;       /* 0x04 */
    u16 nFirstDay;            /* 0x06 */
    u16 nLastDay;             /* 0x08 */
    u16 nCategory;            /* 0x0a: the world */
    u16 nHidden;              /* 0x0c: 1 for a record the list does not count */
    u16 nShownNumber;         /* 0x0e: the number the row shows */
    u16 nTier;                /* 0x10 */
    u16 nBackPayload;         /* 0x12 */
    u8  bSpecial;             /* 0x14 */
    u8  b15;                  /* 0x15 */
    u8  nFlags;               /* 0x16 */
    u8  nCompletionWeight;    /* 0x17 */
    u16 nTimeLimit;           /* 0x18: in seconds */
    u16 nEnemies;             /* 0x1a */
    u16 nInfoFlags;           /* 0x1c */
    u16 nStatA;               /* 0x1e */
    u16 nStatB;               /* 0x20 */
    u8  nStatC;               /* 0x22 */
    u8  nKind;                /* 0x23: 0 the story's row, 4 Mission Mode's, 1/2 its badges */
    u16 nStatD;               /* 0x24 */
    u16 nStatE;               /* 0x26 */
    u16 nRewardKind;          /* 0x28 */
    u16 w2a;                  /* 0x2a */
    u16 w2c;                  /* 0x2c */
    u16 w2e;                  /* 0x2e */
} Ov008MissionListRecord;

/* The list's node of a record. */
typedef struct Ov008MissionListEntry {
    u16 nFileNumber;          /* 0x00 */
    u16 missionId;            /* 0x02 */
    u16 nCategory;            /* 0x04 */
    u16 nShownNumber;         /* 0x06 */
    u16 nTier;                /* 0x08 */
    u16 nBackPayload;         /* 0x0a */
    u8  bSpecial;             /* 0x0c */
    u8  b0d;                  /* 0x0d */
    u8  pad_0e[2];
    int bHidden;              /* 0x10 */
    u8  nFlags;               /* 0x14 */
    u8  completionWeight;     /* 0x15 */
    u8  pad_16[2];
    int nKind;                /* 0x18 */
    int nFirstDay;            /* 0x1c */
    u16 nTimeLimit;           /* 0x20 */
    u16 nEnemies;             /* 0x22 */
    u16 nInfoFlags;           /* 0x24 */
    u8  nStatA;               /* 0x26 */
    u8  nStatB;               /* 0x27 */
    u8  nStatC;               /* 0x28 */
    u8  pad_29;
    u16 nStatD;               /* 0x2a */
    u16 nStatE;               /* 0x2c */
    u16 nRewardKind;          /* 0x2e */
    int n30;                  /* 0x30 */
    int n34;                  /* 0x34 */
    int n38;                  /* 0x38 */
    short *pName;             /* 0x3c */
    short *pBriefing;         /* 0x40 */
    short *pObjective;        /* 0x44 */
    short *pDescFormat;       /* 0x48 */
    u8  pad_4c[0x58 - 0x4c];
} Ov008MissionListEntry;

extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int size);
extern void MI_CpuFill8(void *dst, int val, unsigned int size);
extern short *Ov025_DupWideString(short **cursor, short *in);
Ov008MissionListEntry *Ov025_BuildRecordNode(const Ov008MissionListRecord *pRecord, short *pTexts) {
    short *cur;
    Ov008MissionListEntry *n = (Ov008MissionListEntry *)NNSi_FndAllocFromDefaultExpHeap(0x58);
    MI_CpuFill8(n, 0, 0x58);
    n->nFileNumber = pRecord->nFileNumber;
    n->missionId = pRecord->nMissionNumber;
    n->nCategory = pRecord->nCategory;
    n->nShownNumber = pRecord->nShownNumber;
    n->nTier = pRecord->nTier;
    n->nBackPayload = pRecord->nBackPayload;
    n->bSpecial = pRecord->bSpecial;
    n->bHidden = (pRecord->nHidden == 1);
    n->nFlags = pRecord->nFlags;
    n->b0d = pRecord->b15;
    n->completionWeight = pRecord->nCompletionWeight;
    n->nFirstDay = pRecord->nFirstDay;
    n->nKind = pRecord->nKind;
    n->nTimeLimit = pRecord->nTimeLimit;
    n->nEnemies = pRecord->nEnemies;
    n->nInfoFlags = pRecord->nInfoFlags;
    n->nStatA = (u8)pRecord->nStatA;
    n->nStatB = (u8)pRecord->nStatB;
    n->nStatC = pRecord->nStatC;
    n->nStatD = pRecord->nStatD;
    n->nStatE = pRecord->nStatE;
    n->nRewardKind = pRecord->nRewardKind;
    n->n30 = pRecord->w2a;
    n->n34 = pRecord->w2c;
    n->n38 = pRecord->w2e;
    n->pName = Ov025_DupWideString(&cur, pTexts);
    n->pBriefing = Ov025_DupWideString(&cur, cur);
    n->pObjective = Ov025_DupWideString(&cur, cur);
    n->pDescFormat = Ov025_DupWideString(0, cur);
    return n;
}
