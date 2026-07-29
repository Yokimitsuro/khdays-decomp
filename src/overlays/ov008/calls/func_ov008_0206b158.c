/* func_ov008_0206b158 -- Ov008_RegisterSlotCells (156 B, 8 relocs).
 * Rebuilds the cell list for the current slot page. Looks up the slot table for the page
 * (func_ov008_02069b60 keyed by state->pageId), then for every slot except the currently
 * selected one (state->selected) it registers the slot's inactive-tag cell (table->arrB[i],
 * the byte at +0xd+i) via func_ov008_02055808 + func_ov008_0205589c. Finally it emits the
 * table's group tag (func_ov008_0206abb8(table->id, 0, 0)) and registers the selected slot's
 * active-tag cell (table->arrA[state->selected], the byte at +8). state->selected and
 * table->count are re-read on each iteration. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef short          s16;

typedef struct Ov008SlotState {
    s16 selected;       /* 0x0, signed */
    u16 pageId;         /* 0x2 */
} Ov008SlotState;

typedef struct Ov008SlotTable {
    u16 id;             /* 0x0 */
    u8  count;          /* 0x2 */
    u8  pad_0003[5];
    u8  arrA[5];        /* 0x8, active-tag bytes indexed by state->selected */
    u8  arrB[1];        /* 0xd, inactive-tag bytes indexed by the loop index */
} Ov008SlotTable;

extern Ov008SlotState *func_ov008_02050cd4(void);
extern void *func_ov008_02050c28(void);
extern Ov008SlotTable *func_ov008_02069b60(u16 pageId);
extern void *func_ov008_02055808(void *ctx, int tag);
extern void  func_ov008_0205589c(void *ctx, void *cell);
extern void  func_ov008_0206abb8(u16 tag, int x, int y);

void func_ov008_0206b158(void)
{
    Ov008SlotState *state = func_ov008_02050cd4();
    void *ctx = func_ov008_02050c28();
    Ov008SlotTable *table = func_ov008_02069b60(state->pageId);
    int i;

    for (i = 0; i < table->count; i++) {
        if (state->selected != i) {
            func_ov008_0205589c(ctx, func_ov008_02055808(ctx, table->arrB[i]));
        }
    }
    func_ov008_0206abb8(table->id, 0, 0);
    func_ov008_0205589c(ctx, func_ov008_02055808(ctx, table->arrA[state->selected]));
}
