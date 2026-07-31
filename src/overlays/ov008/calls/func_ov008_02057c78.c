/*
 * Ov008_Menu_ToggleDetailPanel - enter (param_1 != 0) or leave (param_1 == 0) the
 * menu's detail panel, reconfiguring which UI entries are visible and moving the
 * selector.
 *
 * Always records the panel state in shared-context +0x5c6 bit 5 and sets entries
 * 7 and 8 visible to match param_1. On enter it fires the tag-2 callback, hides
 * the main-list entries (0x10/0x11/0x12/0xe/0xf), draws the detail label (var
 * record 0x15) into the widget at +0x4c, snaps the selector (entry 0x15) to that
 * entry saving its position at +0x5cc/+0x5d0, and latches +0x5c6 bit 8. On leave
 * it runs the teardown (func_ov008_02057068), shows the main-list entries again,
 * restores the selector to the saved +0x5cc position, points it at target 0x6b,
 * redraws the menu value, latches bit 8 and records target 0x6b at +0x5c8.
 *
 * Codegen notes:
 *  - The +0x5c6 bit-5 write is a bitfield store (->b5 = param_1); mwcc emits the
 *    lsl16/lsr16/lsl31/bic/orr-lsr26 read-modify-write from that alone.
 *  - func_ov008_02057b7c is called K&R-style (no prototype) so the enter path can
 *    pass 4 args (the selector's nY/nX ride in r2/r3 as the ROM leaves them) while
 *    the leave path passes 2. Caching the context pointer in `gp` keeps it in one
 *    register across the +0x5cc/+0x5d0 store pair (the ROM reuses the now-dead ctx
 *    register), and the 4-arg call forces nX->r3 / nY->r2 so the field loads stay
 *    two ldr (not a coalesced ldm).
 */

typedef struct { int nX; int nY; } UiLayoutPos;
typedef struct {
    unsigned short b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1,
                   b8:1, b9:1, b10:1, b11:1, b12:1, b13:1, b14:1, b15:1;
} Flags;

extern int func_ov008_02050c28(void);
extern int func_ov008_02050c54(void);
extern int func_ov008_02054788(int ctx, int id);
extern void func_ov008_02054ba4(int ctx, int entry, int visible);
extern int func_ov008_02055808(int block, unsigned int tag);
extern void func_ov008_0205589c(int owner, int tag);
extern int func_ov008_02055c84(int recs, int index);
extern void func_02030158(void *surface);
extern void func_02030278(void *widget, int a, int b, int c, void *text, int d);
extern void func_020300f8(void *obj);
extern UiLayoutPos *func_ov008_02054820(int ctx, int entry);
extern void func_ov008_02054858(int ctx, int entry, UiLayoutPos *pos);
extern void func_ov008_02057b7c();
extern void func_ov008_02057068(void);
extern void func_ov008_02057ac4(int ctx);
extern int data_ov008_02090f1c;

void func_ov008_02057c78(int param_1)
{
    int block;
    int ctx;
    int entry;
    int *rec;
    int nX, nY, gp;
    UiLayoutPos *pos;

    block = func_ov008_02050c28();
    ctx = func_ov008_02050c54();
    ((Flags *)(data_ov008_02090f1c + 0x5c6))->b5 = param_1;
    entry = func_ov008_02054788(ctx, 7);
    func_ov008_02054ba4(ctx, entry, param_1);
    entry = func_ov008_02054788(ctx, 8);
    func_ov008_02054ba4(ctx, entry, param_1);
    if (param_1 != 0) {
        entry = func_ov008_02055808(block, 2);
        func_ov008_0205589c(block, entry);
        entry = func_ov008_02054788(ctx, 0x10); func_ov008_02054ba4(ctx, entry, 0);
        entry = func_ov008_02054788(ctx, 0x11); func_ov008_02054ba4(ctx, entry, 0);
        entry = func_ov008_02054788(ctx, 0x12); func_ov008_02054ba4(ctx, entry, 0);
        entry = func_ov008_02054788(ctx, 0xe); func_ov008_02054ba4(ctx, entry, 0);
        entry = func_ov008_02054788(ctx, 0xf); func_ov008_02054ba4(ctx, entry, 0);
        rec = (int *)func_ov008_02055c84(data_ov008_02090f1c + 4, 0x15);
        func_02030158((void *)(data_ov008_02090f1c + 0x4c));
        func_02030278((void *)(data_ov008_02090f1c + 0x4c), 10, 0, 2, rec, 1);
        func_020300f8((void *)(data_ov008_02090f1c + 0x4c));
        entry = func_ov008_02054788(ctx, 0x15);
        pos = func_ov008_02054820(ctx, entry);
        nX = pos->nX;
        nY = pos->nY;
        gp = data_ov008_02090f1c;
        *(int *)(gp + 0x5cc) = nX;
        *(int *)(gp + 0x5d0) = nY;
        func_ov008_02057b7c(1, 8, nY, nX);
        *(unsigned short *)(data_ov008_02090f1c + 0x5c6) |= 0x100;
        return;
    }
    func_ov008_02057068();
    entry = func_ov008_02054788(ctx, 0x10); func_ov008_02054ba4(ctx, entry, 1);
    entry = func_ov008_02054788(ctx, 0x11); func_ov008_02054ba4(ctx, entry, 1);
    entry = func_ov008_02054788(ctx, 0x12); func_ov008_02054ba4(ctx, entry, 1);
    entry = func_ov008_02054788(ctx, 0xe); func_ov008_02054ba4(ctx, entry, 1);
    entry = func_ov008_02054788(ctx, 0xf); func_ov008_02054ba4(ctx, entry, 1);
    entry = func_ov008_02054788(ctx, 0x15);
    func_ov008_02054858(ctx, entry, (UiLayoutPos *)(data_ov008_02090f1c + 0x5cc));
    func_ov008_02057b7c(1, 0x6b);
    func_ov008_02057ac4(data_ov008_02090f1c);
    *(unsigned short *)(data_ov008_02090f1c + 0x5c6) |= 0x100;
    *(int *)(data_ov008_02090f1c + 0x5c8) = 0x6b;
}
