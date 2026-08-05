/*
 * Ov008_MainMenu_SetupToolbar - load the main-menu toolbar/entry resource blocks and set
 * which toolbar entries are visible, called from Ov008_MainMenu_StateTick (state 1).
 *
 * Binds two layout blocks (block 0x12 into the ctx-block at GetCtxBlock4a80, block 0x18 into
 * the main context) from templates data_ov025_020b394c / data_ov025_020b395c, each with its
 * first word overwritten by a resource id. Then, depending on the menu mode flag obj[0x14e0]:
 *   - mode != 0, story flag 0x200d clear: show toolbar entry 2 and release its two slots;
 *   - mode != 0, context object present: show entry 10;
 *   - mode == 0, context object present: show entries 9 and 8, then display a 3-digit counter
 *     (from func_ov025_0208ccbc) across entries 0xf..0x11 - each digit shown unless it and the
 *     remaining higher digits are all zero (leading-zero suppression, but the ones place always
 *     shows).
 *
 * Notes: func_ov025_0208832c (load-block-process-and-free) takes 3 args (ctx, name, id) - the
 * 4th arg Ghidra shows is r3 left over from the 4-word template ldm. func_ov025_0208ccbc is
 * passed obj even though its body ignores it (the caller still loads r0). The digit split is a
 * signed divide-by-10 (val % 10 / val / 10), quotient kept to 16 bits.
 */

typedef unsigned int u32;

typedef struct { u32 f0, f4, f8, fc; } Block4;

extern int  func_ov025_02084a8c(void);
extern int  func_ov025_02084d94(int a);
extern void func_ov025_020883f8(int ctx, Block4 *blk);
extern int  func_ov025_02084d18(int tag);
extern void func_ov025_0208832c(int ctx, char *name, int id);
extern int  func_ov025_02084a7c(void);
extern void func_ov025_02088410(int ctx, void *resName);
extern int  func_02023588(int flag);
extern int  func_ov025_0208843c(int ctx, int id);
extern void func_ov025_0208884c(int ctx, int entry, int a);
extern void func_ov025_020888b0(int ctx, int entry);
extern int  func_ov025_02084e38(void);
extern int  func_ov025_0208ccbc(int obj);
extern void func_ov025_02088928(int ctx, int entry, int digit);
extern Block4 data_ov025_020b394c;
extern Block4 data_ov025_020b395c;

void func_ov025_0208d05c(int obj)
{
    int ctx;
    Block4 blk1;
    Block4 blk2;
    void *resName;
    int entry;
    int i;
    u32 val;
    u32 digit;

    ctx = func_ov025_02084a8c();
    blk1 = data_ov025_020b394c;
    blk2 = data_ov025_020b395c;
    blk1.f0 = func_ov025_02084d94(9);
    func_ov025_020883f8(ctx, &blk1);
    func_ov025_0208832c(ctx, (char *)func_ov025_02084d18(0x12), 0x2b);
    blk2.f0 = func_ov025_02084d18(0x17);
    ctx = func_ov025_02084a7c();
    func_ov025_020883f8(ctx, &blk2);
    resName = (void *)func_ov025_02084d94(8);
    if (resName != 0) {
        func_ov025_02088410(ctx, resName);
    }
    func_ov025_0208832c(ctx, (char *)func_ov025_02084d18(0x18), 0x10);
    if (*(int *)(obj + 0x14e0) != 0 && func_02023588(0x200d) == 0) {
        entry = func_ov025_0208843c(ctx, 2);
        func_ov025_0208884c(ctx, entry, 1);
        func_ov025_020888b0(ctx, entry);
    }
    if (*(int *)(obj + 0x14e0) != 0 && func_ov025_02084e38() != 0) {
        entry = func_ov025_0208843c(ctx, 10);
        func_ov025_0208884c(ctx, entry, 1);
    }
    if (*(int *)(obj + 0x14e0) == 0 && func_ov025_02084e38() != 0) {
        val = func_ov025_0208ccbc(obj);
        entry = func_ov025_0208843c(ctx, 9);
        func_ov025_0208884c(ctx, entry, 1);
        entry = func_ov025_0208843c(ctx, 8);
        func_ov025_0208884c(ctx, entry, 1);
        i = 0;
        do {
            digit = (int)val % 10;
            val = (int)val / 10 & 0xffff;
            if (i == 0 || digit != 0 || val != 0) {
                entry = func_ov025_0208843c(ctx, i + 0xf);
                func_ov025_0208884c(ctx, entry, 1);
                func_ov025_020888b0(ctx, entry);
                func_ov025_02088928(ctx, entry, digit & 0xffff);
            }
            i = i + 1;
        } while (i < 3);
    }
}
