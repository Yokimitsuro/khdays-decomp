/* func_ov025_020b00ec -- Ov025_ReportDetail_Setup: open the report detail view of page B
 * (Ov025_GetPageB 02084b14).  After the common reset (020afdb0) the mode (+0x54) comes from the
 * context field 9768 (enemy profiles rather than reports; 02085078) and the chapter (+0x58) from
 * game-state field 3 (020235d0; +1 while below 6); the background is loaded
 * (Ov025_ReportDetail_LoadBackground 020afdd4), the tag tracker (+0x44; 02084a64) and the entry
 * context (+0x48; 02084a8c) taken, the sprites bound (Ov025_ReportDetail_SetupEntries 020afef4),
 * the text surface built (Ov025_ReportDetail_SetupSurface 020b0090) and the view drawn
 * (Ov025_ReportDetail_Refresh 020b0484).  Always returns 1. */
typedef unsigned char  u8;

typedef struct Ov025ReportDetailPage {
    int  nField00;            /* 0x00 */
    u8   surface[0x3c];       /* 0x04: the text surface (TileSurface) */
    int  nField40;            /* 0x40 */
    int  nTracker;            /* 0x44: the tag tracker */
    int  nCtx;                /* 0x48: the entry context */
    int  nField4c;            /* 0x4c */
    void *pEntry;             /* 0x50: the report shown */
    int  bMissionMode;        /* 0x54: enemy profiles rather than reports */
    int  nChapter;            /* 0x58: GameState field 3, +1 under 6 */
} Ov025ReportDetailPage;

extern Ov025ReportDetailPage *func_ov025_02084b14(void);            /* Ov025_GetPageB */
extern void  func_ov025_020afdb0(void);                             /* Ov025_ReportDetail_Reset */
extern int   func_ov025_02085078(void);                             /* Ov025_GetCtxField9768 */
extern int   func_020235d0(int nField, int nBits);                  /* GameState_GetField */
extern void  func_ov025_020afdd4(void);                             /* Ov025_ReportDetail_LoadBackground */
extern int   func_ov025_02084a64(void);                             /* Ov025_GetCtxBlock954c */
extern int   func_ov025_02084a8c(void);                             /* Ov025_GetBlock4a80 */
extern void  func_ov025_020afef4(void);                             /* Ov025_ReportDetail_SetupEntries */
extern void  func_ov025_020b0090(void);                             /* Ov025_ReportDetail_SetupSurface */
extern void  func_ov025_020b0484(void *pArg);                       /* Ov025_ReportDetail_Refresh: no argument used */

int func_ov025_020b00ec(void *pArg)
{
    Ov025ReportDetailPage *pPage;

    pPage = func_ov025_02084b14();
    func_ov025_020afdb0();
    pPage->bMissionMode = func_ov025_02085078();
    pPage->nChapter = func_020235d0(0x44e, 3);
    if (pPage->nChapter < 6) {
        pPage->nChapter++;
    }
    func_ov025_020afdd4();
    pPage->nTracker = func_ov025_02084a64();
    pPage->nCtx = func_ov025_02084a8c();
    func_ov025_020afef4();
    func_ov025_020b0090();
    func_ov025_020b0484(pArg);
    return 1;
}
