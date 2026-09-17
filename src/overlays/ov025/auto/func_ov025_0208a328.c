/* func_ov025_0208a328 -- Ov025_MissionList_HasVisibleMissionInDays: does the mission table of
 * the list state (+0x14: a u16 count, then variable-length records whose first halfword is
 * their size) hold a mission whose day span (halfwords +6 / +8) lies within nFirstDay..nLastDay
 * and whose hidden halfword (+0xc) is clear?  Returns 1 / 0.  The day list (020ad918) asks this
 * for every day span before it gives the span a row. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov025MissionDayRecord {
    u16  nSize;               /* 0x00: bytes to the next record */
    u16  nField02;            /* 0x02 */
    u16  nField04;            /* 0x04 */
    u16  nFirstDay;                /* 0x06 */
    u16  nLastDay;               /* 0x08 */
    u16  nField0a;            /* 0x0a */
    u16  nHidden;              /* 0x0c */
} Ov025MissionDayRecord;

typedef struct Ov025MissionDayTable {
    u16  nCount;              /* 0x00 */
    Ov025MissionDayRecord aRecord[1]; /* 0x02 */
} Ov025MissionDayTable;

typedef struct Ov008MissionListState {
    u8   pad_00[0x14];
    Ov025MissionDayTable *pDayTable; /* 0x14: the resource data */
} Ov008MissionListState;

int func_ov025_0208a328(Ov008MissionListState *pState, u32 nFirstDay, u32 nLastDay)
{
    int i;
    Ov025MissionDayRecord *pRecord;   /* declared before nCount: ip / lr in this order */
    int nCount;

    nCount = pState->pDayTable->nCount;
    pRecord = pState->pDayTable->aRecord;
    for (i = 0; i < nCount; i++) {
        if (pRecord->nFirstDay >= nFirstDay && pRecord->nLastDay <= nLastDay && pRecord->nHidden == 0) {
            return 1;
        }
        pRecord = (Ov025MissionDayRecord *)((u8 *)pRecord + pRecord->nSize);
    }
    return 0;
}
