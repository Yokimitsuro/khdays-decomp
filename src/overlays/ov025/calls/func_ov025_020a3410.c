/* func_ov025_020a3410 -- Ov008_DrawStatusPage (712 B, 36 relocs).
 * Stats/status menu page render state. Draws six labelled stat fields (record indices 4,7,5,8,6,0xc
 * off ctx+0x58) into the ctx+0x118 layer, then pushes the numeric values through the variadic
 * setter func_ov025_020a41f0 (ids 1, 9, 0xe, 0x10, 0x14, 0x12, 0x13, 0xf) sourced from the global
 * record at data_0204be18 and from game-state field 0x44e. When LoadGlobalShort (func_02024e5c)
 * reports state 3 it briefly swaps ctx+0x138 around the fourth draw. A message-record scan
 * (func_020342e8 / func_020343cc) over up to 99 entries computes a remaining count that feeds the
 * final eb64(0xf) call, then it builds the menu list and enqueues the five layer gfx commands.
 *
 * func_ov025_020a41f0 is variadic (id, flag, ...): the callers pass zero, one, or two value
 * registers. eq3/counter must be declared before uVar9 so the coalesced eq3+counter live range
 * takes r7 and uVar9 takes r8, matching the ROM. */
typedef unsigned char  u8;
typedef unsigned short u16;

extern char *data_0204be18;

extern int   func_ov025_02084c84(void);
extern int   func_ov025_02084cb4(void);
extern int  *func_ov025_02089894(int base, int id);
extern void  func_02030278(int dctx, int x, int y, int mode, int rec, int flag);
extern int   func_02024e5c(void);
extern int   func_ov025_020a41f0(int id, int a, ...);
extern int   func_020235d0(int id, int field);
extern void  func_020342e8(int *rec, int a, int b, int c);
extern void  func_020343cc(int *rec);
extern void  func_ov025_020a4890(void *ids);
extern void  func_020300f8(int dctx);

void func_ov025_020a3410(int ctx)
{
    int eq3, counter;
    int uVar9 = 0;
    int local_28 = 0;
    int a = func_ov025_02084c84();
    int b = func_ov025_02084cb4();
    int *rec;

    rec = func_ov025_02089894(ctx + 0x58, 4);
    func_02030278(ctx + 0x118, 5, 7, 0xf2, (int)rec, 1);
    rec = func_ov025_02089894(ctx + 0x58, 7);
    func_02030278(ctx + 0x118, 0x59, 7, 0xf2, (int)rec, 1);
    rec = func_ov025_02089894(ctx + 0x58, 5);
    func_02030278(ctx + 0x118, 5, 0x17, 0xf2, (int)rec, 1);

    rec = func_ov025_02089894(ctx + 0x58, 8);
    eq3 = func_02024e5c() == 3;
    if (eq3)
        *(int *)(ctx + 0x138) = b;
    func_02030278(ctx + 0x118, 0x59, 0x17, 0xf2, (int)rec, 1);
    if (eq3)
        *(int *)(ctx + 0x138) = a;

    rec = func_ov025_02089894(ctx + 0x58, 6);
    func_02030278(ctx + 0x118, 5, 0x27, 0xf2, (int)rec, 1);
    rec = func_ov025_02089894(ctx + 0x58, 0xc);
    func_02030278(ctx + 0x118, 5, 0x57, 0xf2, (int)rec, 1);

    func_ov025_020a41f0(1, 0);
    func_ov025_020a41f0(9, 0, 0x64);
    func_ov025_020a41f0(0xe, 0, *(int *)(data_0204be18 + 4));
    func_ov025_020a41f0(0x10, 0, 0);
    func_ov025_020a41f0(0x14, 0, 6);
    func_ov025_020a41f0(0x12, 0, *(u16 *)(data_0204be18 + 0x196a),
                        *(u16 *)(data_0204be18 + 0x1968));
    if (func_020235d0(0x44e, 3) != 0)
        func_ov025_020a41f0(0x13, 0, func_020235d0(0x44e, 3) + 0xe);

    counter = 1;
    while (1) {
        int uVar7, field4;
        func_020342e8(&local_28, 0x1c, counter, 0xe);
        uVar7 = *(int *)(local_28 + 0xc);
        if (uVar7 < 0) {
            uVar9 = -1;
            func_020343cc(&local_28);
            break;
        }
        field4 = *(int *)(data_0204be18 + 4);
        if ((unsigned)uVar7 > (unsigned)field4) {
            uVar9 = uVar7 - field4;
            func_020343cc(&local_28);
            break;
        }
        func_020343cc(&local_28);
        counter++;
        if (counter >= 0x64)
            break;
    }

    func_ov025_020a41f0(0xf, 0, uVar9);
    func_ov025_020a4890(data_0204be18 + 0xee0);
    func_020300f8(ctx + 0x64);
    func_020300f8(ctx + 0xa0);
    func_020300f8(ctx + 0xdc);
    func_020300f8(ctx + 0x118);
    func_020300f8(ctx + 0x154);
}
