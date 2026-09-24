/* func_ov025_020a0428 -- Ov025_Reports_RefreshRowEntries: set the sprite entries of the ten rows
 * (+0xd0, seven entries each) for the records from the window top (+0).  A report row within
 * the count (+4) shows its title, its number in the three digit entries (leading zeros hidden;
 * Ov025_SetEntryCell 02088928), the mark for bit 9 of the record, the badge with the item flags
 * (Ov025_QueryItemFlags 0209e820 for the record, or its read variant +0x40, when they are 0 / 1)
 * and the read-variant mark when the record has one (+0xc).  An enemy profile row, or a row past
 * the count, hides the title, digits and mark and shows the read-variant mark only for a record
 * with nothing pending, and the badge (flags of the record itself; always hidden for reports)
 * only then too. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef short          s16;

typedef struct Ov025ReportsEntry {
    u16  nId : 9;             /* 0x00 bits 0-8 */
    u16  nFlag9 : 1;          /* 0x00 bit 9: the mark entry */
    u16  nPending : 6;        /* 0x00 bits 10-15: enemies still to defeat */
    u8   pad_02[0xa];
    struct Ov025ReportsEntry *pRead; /* 0x0c: the read variant of the record, if any */
    u8   pad_10[0x40 - 0x10];
} Ov025ReportsEntry;          /* 0x40 */

typedef struct Ov025ReportsRow {
    void *pTitle;             /* 0x00: entry 0x33 + row */
    void *apDigit[3];         /* 0x04: entries 0x3d / 0x47 / 0x51 + row: the report number */
    void *pMark;              /* 0x10: entry 0x5b + row */
    void *pBadge;             /* 0x14: entry 0x6f + row: the owned / seen badge */
    void *pNumber;            /* 0x18: entry 0x65 + row: the read-variant mark */
} Ov025ReportsRow;            /* 0x1c */

typedef struct Ov025ReportsPage {
    s16  nTop;                /* 0x000: the first visible report */
    s16  nCursor;             /* 0x002 */
    s16  nCount;              /* 0x004 */
    s16  nField06;            /* 0x006 */
    u8   pad_008[0xb8 - 0x8];
    int  nCtx;                /* 0x0b8: the entry context */
    u8   pad_0bc[0xd0 - 0xbc];
    Ov025ReportsRow aRow[10]; /* 0x0d0 */
    Ov025ReportsEntry *pEntries; /* 0x1e8: the per-report records */
    u8   pad_1ec[0x258 - 0x1ec];
    int  bMissionMode;        /* 0x258: enemy profiles rather than reports */
} Ov025ReportsPage;

extern Ov025ReportsPage *func_ov025_02084afc(void);                 /* Ov008_GetPageA */
extern u32   func_ov025_0209e820(u32 nItem, u32 bSet);              /* Ov025_QueryItemFlags */
extern void  func_ov025_0208884c(int nCtx, void *pEntry, int bVisible); /* SetEntrySlotsVisible */
extern void  func_ov025_02088928(int nCtx, void *pEntry, int nCell); /* Ov025_SetEntryCell */

void func_ov025_020a0428(void)
{
    Ov025ReportsPage *pPage;
    Ov025ReportsEntry *pEntry;
    int i;
    int nId;
    Ov025ReportsRow *pRow;
    int j;
    Ov025ReportsEntry *pEnd;

    pPage = func_ov025_02084afc();
    pEnd = &pPage->pEntries[pPage->nCount];
    pRow = pPage->aRow;
    for (i = 0; i < 10; i++) {
        pEntry = &(pPage->pEntries + pPage->nTop)[i];
        if (pPage->bMissionMode == 0 && pEntry < pEnd) {
            u32 nFlags = func_ov025_0209e820(i + (pPage->nTop + (pEntry->pRead != 0 ? 0x40 : 0)), 0);
            u32 alias = (u32)nFlags;
            func_ov025_0208884c(pPage->nCtx, pRow->pTitle, 1);
            nId = pEntry->nId;
            for (j = 0; j < 3; j++) {
                func_ov025_02088928(pPage->nCtx, pRow->apDigit[j], (u16)(nId % 10));
                func_ov025_0208884c(pPage->nCtx, pRow->apDigit[j], (j == 0 || nId != 0) ? 1 : 0);
                nId /= 10;
            }
            func_ov025_0208884c(pPage->nCtx, pRow->pMark, pEntry->nFlag9);
            func_ov025_0208884c(pPage->nCtx, pRow->pBadge, (int)alias < 2 ? 1 : 0);
            if ((int)nFlags < 2) {
                func_ov025_02088928(pPage->nCtx, pRow->pBadge, (u16)nFlags);
            }
            func_ov025_0208884c(pPage->nCtx, pRow->pNumber, pEntry->pRead != 0 ? 1 : 0);
        } else {
            u32 nFlags;
            if (pPage->bMissionMode == 0) {
                nFlags = 3;
            } else {
                nFlags = func_ov025_0209e820(pPage->nTop + i, 0);
            }
            func_ov025_0208884c(pPage->nCtx, pRow->pTitle, 0);
            func_ov025_0208884c(pPage->nCtx, pRow->apDigit[0], 0);
            func_ov025_0208884c(pPage->nCtx, pRow->apDigit[1], 0);
            func_ov025_0208884c(pPage->nCtx, pRow->apDigit[2], 0);
            func_ov025_0208884c(pPage->nCtx, pRow->pMark, 0);
            func_ov025_0208884c(pPage->nCtx, pRow->pNumber, (pEntry->pRead != 0 && pEntry->nPending == 0) ? 1 : 0);
            func_ov025_0208884c(pPage->nCtx, pRow->pBadge, (pEntry->nPending == 0 && (int)nFlags < 2) ? 1 : 0);
            if ((int)nFlags < 2) {
                func_ov025_02088928(pPage->nCtx, pRow->pBadge, (u16)nFlags);
            }
        }
        pRow++;
    }
}
