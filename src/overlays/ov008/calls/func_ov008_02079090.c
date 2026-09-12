/* func_ov008_02079090 -- Ov008_MovePageBUp: move page B's cursor up one row.  Past
 * the top it wraps to the last row when a cue request is pending (else it stays on
 * row 0 and nothing else happens); a wrap that lands on row 0 is silent too.  Any
 * real move drains the double count for the new row, starts the collapse slide and
 * plays the move sound.
 */
typedef unsigned char u8;

typedef struct Ov008PageB {
    u8  pad_000[0x1e8];
    int nRow;                 /* 0x1e8 */
    u8  pad_1ec[0x200 - 0x1ec];
    u8  list[4];              /* 0x200: ov025 list */
} Ov008PageB;

typedef struct Ov008CueRequest {
    u8  pad_00[0xc];
    int bWrap;                /* 0x0c */
} Ov008CueRequest;

#define SOUND_MOVE 2

extern Ov008PageB *func_ov008_02050cec(void);              /* Ov008_GetPageB */
extern int func_ov008_0207890c(void);                      /* Ov008_IsEntryBusyOrInactive */
extern Ov008CueRequest *func_ov008_02051198(void);         /* Ov008_GetCueRequest */
extern short func_ov025_020b0850(void *pList);             /* list scroll total */
extern void func_ov008_02079050(int nRow);                 /* Ov008_DrainDoubleCount */
extern void func_ov008_02078954(void);                     /* collapse slide */
extern void func_02033b78(int nKind, int nSound);          /* PlaySound */

void func_ov008_02079090(void)
{
    Ov008PageB *pPage = func_ov008_02050cec();
    int nRow;

    if (func_ov008_0207890c() != 0) {
        return;
    }
    nRow = pPage->nRow - 1;
    pPage->nRow = nRow;
    if (nRow < 0) {
        if (func_ov008_02051198()->bWrap != 0) {
            nRow = func_ov025_020b0850(pPage->list) - 1;
            pPage->nRow = nRow;
            if (nRow == 0) {
                return;
            }
            func_ov008_02079050(nRow);
            func_ov008_02078954();
            func_02033b78(0, SOUND_MOVE);
        } else {
            pPage->nRow = 0;
        }
        return;
    }
    func_ov008_02079050(nRow);
    func_ov008_02078954();
    func_02033b78(0, SOUND_MOVE);
}
