/* func_ov025_020afb70 -- Ov008_MovePageBDown: move page B's cursor down one row.
 * With a cue request pending the row advances and wraps to 0 past the end (the
 * wrap resets the ov025 list, and is silent when the list has fewer than two
 * rows); without one the row only advances while a row below exists.  Any real
 * move starts the collapse slide and plays the move sound.
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

extern Ov008PageB *func_ov025_02084b14(void);              /* Ov008_GetPageB */
extern int func_ov025_020af364(void);                      /* Ov008_IsEntryBusyOrInactive */
extern Ov008CueRequest *func_ov025_02084fa8(void);         /* Ov008_GetCueRequest */
extern short func_ov025_020b0850(void *pList);             /* list scroll total */
extern void func_ov025_020b0888(void *pList);              /* list reset */
extern void func_ov025_020af3ac(void);                     /* collapse slide */
extern void func_02033b78(int nKind, int nSound);          /* PlaySound */

void func_ov025_020afb70(void)
{
    Ov008PageB *pPage = func_ov025_02084b14();

    if (func_ov025_020af364() != 0) {
        return;
    }
    if (func_ov025_02084fa8()->bWrap != 0) {
        pPage->nRow++;
        if (pPage->nRow >= func_ov025_020b0850(pPage->list)) {
            pPage->nRow = 0;
            /* unsigned `> 1`: the ROM tests the total with cmp #1 / popls */
            if ((unsigned int)(int)func_ov025_020b0850(pPage->list) > 1) {
                func_ov025_020b0888(pPage->list);
                func_ov025_020af3ac();
                func_02033b78(0, SOUND_MOVE);
            }
        } else {
            func_ov025_020af3ac();
            func_02033b78(0, SOUND_MOVE);
        }
    } else {
        if (pPage->nRow + 1 < func_ov025_020b0850(pPage->list)) {
            func_ov025_020af3ac();
            func_02033b78(0, SOUND_MOVE);
            pPage->nRow++;
        }
    }
}
