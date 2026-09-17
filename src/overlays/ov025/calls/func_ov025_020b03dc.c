/* func_ov025_020b03dc -- Ov025_ReportDetail_DrawLines: draw the chapter lines of a report on
 * the detail view of page B (Ov025_GetPageB 02084b14).  String 1 of the reports text
 * (Ov025_Reports_GetString 020a0f00) heads the column at (0x12, 0x2b) in colour 0x209 with a
 * drop shadow (Ov025_DrawStringShadowed 020b0250); then six rows 16 pixels apart: for the
 * chapters below the page's (+0x58) the record's line (+0x28 + 4 * chapter), or string 2 when
 * it has none, and "????????" (data_ov025_020b5724) for the chapters not reached. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov025ReportsEntry {
    u16  nId : 9;             /* 0x00 bits 0-8 */
    u16  nFlag9 : 1;          /* 0x00 bit 9 */
    u16  nPending : 6;        /* 0x00 bits 10-15: enemies still to defeat */
    u8   pad_02[8];
    u8   bUnlocked;           /* 0x0a */
    u8   nField0b;            /* 0x0b */
    struct Ov025ReportsEntry *pRead; /* 0x0c: the read variant of the record, if any */
    const u16 *pName;         /* 0x10: the title */
    u8   pad_14[4];
    const u16 *pText;         /* 0x18 */
    u8   pad_1c[0xc];
    const u16 *apLine[6];     /* 0x28: one line per chapter */
} Ov025ReportsEntry;          /* 0x40 */

typedef struct Ov025ReportDetailPage {
    int  nField00;            /* 0x00 */
    u8   surface[0x3c];       /* 0x04: the text surface (TileSurface) */
    int  nField40;            /* 0x40 */
    int  nTracker;            /* 0x44: the tag tracker */
    int  nCtx;                /* 0x48: the entry context */
    int  nField4c;            /* 0x4c */
    Ov025ReportsEntry *pEntry; /* 0x50: the report shown */
    int  bMissionMode;        /* 0x54: enemy profiles rather than reports */
    int  nChapter;            /* 0x58: GameState field 3, +1 under 6 */
    void *pTitleEntry;        /* 0x5c: entry 0 */
    void *apDigit[3];         /* 0x60: entries 1..3 */
    void *pMarkEntry;         /* 0x6c: entry 4 */
    void *pCountEntry;        /* 0x70: entry 5 */
    void *pSlashEntry;        /* 0x74: entry 7 */
    void *pTotalEntry;        /* 0x78: entry 6 */
    void *pEntry8;            /* 0x7c: entry 8 */
    void *pEntry9;            /* 0x80: entry 9 */
} Ov025ReportDetailPage;      /* 0x84 */

typedef struct Ov025ReportDetailSet {
    u8   nBgMember;           /* 0x00: the background archive member */
    u8   nLayoutMember;       /* 0x01 */
    u8   nEntriesMember;      /* 0x02 */
} Ov025ReportDetailSet;

typedef struct Ov025ReportDetailText {
    u8   nCharSubFile;        /* 0x00: the localised BG3 characters (0 = the background's own) */
    u8   nResource;           /* 0x01: the resource by index */
} Ov025ReportDetailText;

extern Ov025ReportDetailPage *func_ov025_02084b14(void);            /* Ov025_GetPageB */
extern const u16 *func_ov025_020a0f00(int nString);                 /* Ov025_Reports_GetString */
extern void  func_ov025_020b0250(int nX, int nY, int nColour, u32 nFlags, const u16 *pText); /* Ov025_DrawStringShadowed */
extern const u16 data_ov025_020b5724[];                             /* "????????" */

void func_ov025_020b03dc(Ov025ReportsEntry *pEntry)
{
    Ov025ReportDetailPage *pPage;
    int i;
    int nY;
    const u16 *pText;

    pPage = func_ov025_02084b14();
    nY = 0x2b;
    func_ov025_020b0250(0x12, nY, 6, 0x209, func_ov025_020a0f00(1));
    for (i = 0; i < 6; i++) {
        nY += 0x10;
        if (i < pPage->nChapter) {
            pText = pEntry->apLine[i];
            if (pText == 0) {
                pText = func_ov025_020a0f00(2);
            }
        } else {
            pText = data_ov025_020b5724;
        }
        func_ov025_020b0250(0x12, nY, 6, 0x209, pText);
    }
}
