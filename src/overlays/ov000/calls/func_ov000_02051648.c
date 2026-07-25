/* Draws the per-slot text of the three save slots on the Load screen, called by
 * Ov000_TickPageScroll every frame once the pages have been repositioned.
 *
 * Forwards its scroll arguments to the text object at ctx+0x4d38, then walks the three
 * slot records. State 2 draws the single "empty slot" string (var record 0xd). State 1
 * formats and draws seven fields at fixed x-offsets from the slot's own Q12 position:
 * world name (record 0xc), level (record 6), the play time split into H/M/S by
 * func_ov000_02050548, and two counters (record 0xb). Every field shifts down by 8 when
 * bExtraEntryActive is set. Ends by enqueuing the object's draw command.
 *
 * CODEGEN NOTES -- three separate decisions, none of them obvious from the
 * disassembly, and each one worth knowing on its own:
 *
 *  1. `func_020262a0` is VARIADIC. Cases 5 and 6 leave r3 untouched before the call,
 *     which is only reachable if those two call sites pass three arguments and the
 *     prototype has an ellipsis. Declared with four fixed parameters the function is
 *     correct C and the wrong code.
 *
 *  2. The k==3 / k==4 arm must be written `if (k != 3) { if (k == 4) ... } else ...`.
 *     Written as `if (k == 3) ... else if (k == 4) ...` mwcc if-converts the k==3 body
 *     into predicated instructions; the ROM branches instead and therefore keeps the
 *     value in a callee-saved register across the merge. That extra long-lived value is
 *     what pushes `by` out of a register and onto the frame -- so getting this wrong
 *     leaves the function 28 bytes short, and the cause is nowhere near the symptom.
 *
 *  3. `const` on the cached context pointer decides the FRAME LAYOUT. mwcc groups
 *     stack locals, and an unqualified pointer local lands BELOW the ints while
 *     `Ov000LoadPageContext *const ctx` lands above them. With the pointer below, the
 *     five scalar slots come out rotated (ctx/off/by at 8/0xc/0x18 instead of the ROM's
 *     0x18/8/0xc) and no permutation of the declarations can fix it -- 121 declaration
 *     positions were compiled and every one gave ctx at slot 8. The qualifier is the
 *     only lever that moves it.
 *
 * A fourth, smaller one: `dx` is a function-scope int, not a loop-local. As a
 * loop-local it takes r8 and pushes `rec` to r7, the exact reverse of the ROM.
 */

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov000Pair {
    int x;
    int y;
} Ov000Pair;

typedef struct Ov000SaveSlot {
    u8  pad_00[2];
    u16 wWorldId;
    int nLevel;
    u8  pad_08[4];
    u32 dwPlayTime;
    u8  pad_10[4];
    int nSlotState;
    u8  pad_18[8];
} Ov000SaveSlot;

typedef struct Ov000LoadPageContext {
    u8 pad_0000[0x4acc];
    u8 bExtraEntryActive;
    u8 pad_4acd[0x4b10 - 0x4acd];
    Ov000SaveSlot aSlot[3];
    u8 pad_4b70[0x4cb4 - 0x4b70];
    u8 aVarTable[0x4d38 - 0x4cb4];
    u8 aTextObject[1];
} Ov000LoadPageContext;

typedef struct Ov000LoadPageContextB {
    u8 pad_0000[0x4c];
    u8 aSelectionObject[1];
} Ov000LoadPageContextB;

extern Ov000LoadPageContext *data_ov000_0205ac24;
extern const u16 data_ov000_0205aad8[];

extern void func_02030158(u8 *obj, int a, int b, int c);
extern int  func_ov000_02055b48(u8 *obj, int id);
extern Ov000Pair *func_ov000_02055bc4(u8 *obj, int entry);
extern u16 *func_ov000_02056970(u8 *table, int index);
extern void func_ov000_0205039c(u8 *obj, int x, int y, int a, u16 *text, int mode);
extern void func_ov000_02050548(u32 t, u16 *h, u8 *m, u8 *s);
extern void func_020262a0(u16 *buf, int size, const u16 *fmt, ...);
extern void func_020300f8(u8 *obj);

void func_ov000_02051648(int a1, int a2, int a3, int a4)
{
    Ov000LoadPageContext *const ctx = data_ov000_0205ac24;
    int slot;
    int bx;
    int by;
    int k;
    int entry;
    Ov000Pair *p;
    int dx;
    Ov000SaveSlot *rec;
    u16 buf[128];
    u16 wHours;
    u8 bSeconds;
    u8 bMinutes;

    func_02030158(ctx->aTextObject, a2, a3, a4);

    for (slot = 0; slot < 3; slot++) {
        rec = &data_ov000_0205ac24->aSlot[slot];
        entry = func_ov000_02055b48(((Ov000LoadPageContextB *)ctx)->aSelectionObject,
                                    slot + 1);
        p = func_ov000_02055bc4(((Ov000LoadPageContextB *)ctx)->aSelectionObject, entry);
        bx = p->x >> 12;
        by = (p->y >> 12) - 0x20;
        if (rec->nSlotState == 2) {
            u16 *text = func_ov000_02056970(data_ov000_0205ac24->aVarTable, 0xd);
            int dy = 0xc;
            if (data_ov000_0205ac24->bExtraEntryActive != 0) {
                dy += 8;
            }
            func_ov000_0205039c(data_ov000_0205ac24->aTextObject, bx + 0x37, by + dy,
                                4, text, 0);
        } else if (rec->nSlotState == 1) {
            func_ov000_02050548(rec->dwPlayTime, &wHours, &bMinutes, &bSeconds);
            for (k = 0; k < 7; k++) {
                int dy;
                int mode;
                dx = 0x1b;
                dy = 0x17;
                switch (k) {
                case 0:
                    func_020262a0(buf, 0x80,
                                  func_ov000_02056970(data_ov000_0205ac24->aVarTable, 0xc),
                                  rec->wWorldId);
                    dx += 2;
                    mode = 0;
                    break;
                case 1:
                    func_020262a0(buf, 0x80,
                                  func_ov000_02056970(data_ov000_0205ac24->aVarTable, 6),
                                  rec->nLevel);
                    dx += 0x70;
                    mode = 1;
                    break;
                case 2:
                    dx += 0x89;
                    func_020262a0(buf, 0x80, data_ov000_0205aad8, wHours);
                    mode = 1;
                    break;
                case 3:
                case 4:
                    {
                        u8 v;
                        if (k != 3) {
                            if (k == 4) {
                                dx += 0xa0;
                                v = bSeconds;
                            }
                        } else {
                            v = bMinutes;
                            dx += 0x92;
                        }
                        func_020262a0(buf, 0x80, data_ov000_0205aad8, v);
                    }
                    mode = 2;
                    break;
                case 5:
                case 6:
                    func_020262a0(buf, 0x80,
                                  func_ov000_02056970(data_ov000_0205ac24->aVarTable, 0xb));
                    dx += (k == 5) ? 0x8c : 0x9a;
                    mode = 1;
                    break;
                default:
                    continue;
                }
                if (data_ov000_0205ac24->bExtraEntryActive != 0) {
                    dy += 8;
                }
                func_ov000_0205039c(data_ov000_0205ac24->aTextObject, bx + dx, by + dy,
                                    2, buf, mode);
            }
        }
    }
    func_020300f8(data_ov000_0205ac24->aTextObject);
}
