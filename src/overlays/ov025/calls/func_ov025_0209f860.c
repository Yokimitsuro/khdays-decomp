/* func_ov025_0209f860 -- Ov025_Reports_CountUnlocked: count the reports the player can open and
 * link the read variants.  In enemy-profile mode (+0x258 == 1) every record of the table (+0x230)
 * counts (+4).  Otherwise the records (+0x1e8) count from the first while their id (a day) is
 * below the current day (game-state field 9; 359 once the story chapter, field 3, is 6), the next
 * record's day is not beyond it and the record is unread (+0xb); then, with the mission and
 * challenge lists of overlay 0x12e loaded (data_ov025_020b4234, kinds 5 / 6; 0208a13c), each
 * remaining record whose day span (data_ov025_020b4278[record - 60]) is complete
 * (Ov025_Reports_IsDaySpanComplete 0209f774, final chapter only) becomes the read variant (+0xc)
 * of the counted record with the same id.  A first record with nothing pending marks item 0 as
 * owned (Ov025_QueryItemFlags 0209e820). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef short          s16;

typedef struct Ov008MissionResourceDescriptor {
    const char *pszPath;      /* 0x00: "UI/cm/msl_&.msi.z" */
    int  nSelector;           /* 0x04 */
    int  nListKind;           /* 0x08: 5 = missions, 6 = challenges */
} Ov008MissionResourceDescriptor;

typedef struct Ov008MissionListState {
    u8   data[0x24];
} Ov008MissionListState;

typedef struct Ov025ReportsEntry {
    u16  nId : 9;             /* 0x00 bits 0-8 */
    u16  nFlag9 : 1;          /* 0x00 bit 9 */
    u16  nPending : 6;        /* 0x00 bits 10-15: enemies still to defeat */
    u8   pad_02[9];
    u8   bRead;               /* 0x0b */
    struct Ov025ReportsEntry *pRead; /* 0x0c: the read variant of the record, if any */
    u8   pad_10[0x40 - 0x10];
} Ov025ReportsEntry;          /* 0x40 */

typedef struct Ov025ReportsPage {
    s16  nTop;                /* 0x000: the first visible report */
    s16  nCursor;             /* 0x002 */
    s16  nCount;              /* 0x004 */
    u8   pad_006[0x1e8 - 0x6];
    Ov025ReportsEntry *pEntries; /* 0x1e8: the per-report records */
    u8   pad_1ec[0x230 - 0x1ec];
    const u32 *pTable;        /* 0x230: the report table file (its first word counts the records) */
    u8   pad_234[0x258 - 0x234];
    int  bMissionMode;        /* 0x258: enemy profiles rather than reports */
} Ov025ReportsPage;

typedef struct Ov025DaySpan {
    u16  nFirstDay;           /* 0x00 */
    u16  nLastDay;            /* 0x02 */
} Ov025DaySpan;

extern Ov025ReportsPage *func_ov025_02084afc(void);                 /* Ov008_GetPageA */
extern u32   func_020235d0(int nField, int nBits);                  /* GameState_GetField */
extern void  func_0201e470(int nAsync, int nOverlay);               /* LoadOverlaySync */
extern void  func_0201e4a8(int nAsync, int nOverlay);               /* UnloadOverlaySync */
extern void  func_ov025_0208a13c(Ov008MissionListState *pList, Ov008MissionResourceDescriptor *pDescriptor); /* Ov025_InitMissionList */
extern void  func_ov025_0208a19c(Ov008MissionListState *pList);     /* Ov025_ReleaseMissionList */
extern int   func_ov025_0209f774(Ov008MissionListState *pMissions, Ov008MissionListState *pChallenges, const Ov025DaySpan *pSpan); /* Ov025_Reports_IsDaySpanComplete */
extern u32   func_ov025_0209e820(u32 nItem, u32 bSet);              /* Ov025_QueryItemFlags */
extern const Ov008MissionResourceDescriptor data_ov025_020b4234;
extern const Ov025DaySpan data_ov025_020b4278[];                    /* the day spans of the reports from record 60 on */

void func_ov025_0209f860(void)
{
    Ov025ReportsPage *pPage;
    u16 nDay;
    int bFinal;
    u32 nTotal;
    u16 i;
    u16 j;
    u16 nCount;
    Ov008MissionResourceDescriptor desc;
    Ov008MissionListState missions;
    Ov008MissionListState challenges;

    pPage = func_ov025_02084afc();
    nDay = func_020235d0(0, 9);
    bFinal = func_020235d0(0x44e, 3) == 6;
    desc = data_ov025_020b4234;
    if (bFinal) {
        nDay = 359;
    }
    if (pPage->bMissionMode == 1) {
        pPage->nCount = *pPage->pTable;
    } else {
        nTotal = *pPage->pTable;
        i = 0;
        nCount = 0;
        while (i < nTotal) {
            if (pPage->pEntries[i].nId >= nDay) {
                break;
            }
            if (i + 1 <= nTotal && pPage->pEntries[i + 1].nId > nDay) {
                break;
            }
            if (pPage->pEntries[i].bRead != 0) {
                break;
            }
            nCount++;
            i++;
        }
        pPage->nCount = nCount;
        func_0201e470(0, 0x12e);
        func_ov025_0208a13c(&missions, &desc);
        desc.nListKind = 6;
        func_ov025_0208a13c(&challenges, &desc);
        for (; i < *pPage->pTable; i++) {
            for (j = 0; j < nCount; j++) {
                if (pPage->pEntries[i].nId == pPage->pEntries[j].nId) {
                    break;
                }
            }
            if (bFinal && func_ov025_0209f774(&missions, &challenges, &data_ov025_020b4278[i] - 60) != 0) {
                pPage->pEntries[j].pRead = &pPage->pEntries[i];
            }
        }
        func_ov025_0208a19c(&challenges);
        func_ov025_0208a19c(&missions);
        func_0201e4a8(0, 0x12e);
    }
    if (pPage->pEntries[0].nPending == 0) {
        func_ov025_0209e820(0, 1);
    }
}
