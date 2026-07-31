/*
 * Ov008_Menu_PositionSelector - show/hide the selector element (entry 0x15) and,
 * when a target entry is given, move it to track that entry.
 *
 * Always sets the visibility of entry 0x15 to param_1. If param_2 is a real entry
 * id (not -1) it also: swaps that entry's parameter overrides in, records it as the
 * active target at (*data_ov008_02090f1c + 0x88), and repositions entry 0x15.
 * The selector's X comes from entry 0x15's own layout X normally, but when the
 * shared context exists and its +0x5c6 bit 5 is set it instead sits 0x30000 (3px,
 * 16.16 fixed) left of the target entry; the Y always follows the target entry.
 *
 * Codegen notes: the +0x5c6 test is a 16-bit bitfield (->b5), matching the ROM's
 * ldrh;lsl;lsr; the `|| ->b5 == 0` short-circuits so the +0x5c6 deref is skipped
 * when the context pointer is null. func_ov008_02054cc4 takes two args (the r2 live
 * at that call is stale, not param_1).
 */

typedef struct { int nX; int nY; } UiLayoutPos;
typedef struct {
    unsigned short b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1,
                   b8:1, b9:1, b10:1, b11:1, b12:1, b13:1, b14:1, b15:1;
} Flags;

extern int func_ov008_02050c54(void);
extern int func_ov008_02054788(int ctx, int id);
extern void func_ov008_02054ba4(int ctx, int entry, int visible);
extern void func_ov008_02054cc4(int ctx, int entry);
extern UiLayoutPos *func_ov008_02054820(int ctx, int entry);
extern void func_ov008_02054858(int ctx, int entry, UiLayoutPos *pos);
extern int data_ov008_02090f1c;

void func_ov008_02057b7c(int param_1, int param_2, int param_3, int param_4)
{
    int ctx;
    int entry15;
    int pEntry;
    int pEntry15;
    UiLayoutPos *pos15;
    UiLayoutPos *posSel;
    UiLayoutPos pos;

    ctx = func_ov008_02050c54();
    entry15 = func_ov008_02054788(ctx, 0x15);
    func_ov008_02054ba4(ctx, entry15, param_1);
    if (param_2 == -1) return;

    pEntry = func_ov008_02054788(ctx, param_2);
    func_ov008_02054cc4(ctx, pEntry);
    *(int *)(data_ov008_02090f1c + 0x88) = param_2;
    pEntry15 = func_ov008_02054788(ctx, 0x15);
    pos15 = func_ov008_02054820(ctx, pEntry15);
    posSel = func_ov008_02054820(ctx, pEntry);
    if (data_ov008_02090f1c == 0 ||
        ((Flags *)(data_ov008_02090f1c + 0x5c6))->b5 == 0) {
        pos.nX = pos15->nX;
        pos.nY = posSel->nY;
    } else {
        pos.nX = posSel->nX - 0x30000;
        pos.nY = posSel->nY;
    }
    func_ov008_02054858(ctx, pEntry15, &pos);
}
