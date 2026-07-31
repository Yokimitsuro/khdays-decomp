/*
 * Ov008_Menu_RefreshSubitemGrid - per-frame refresh of the menu's sub-item
 * availability grid (the second of the two setup steps run on menu tick).
 *
 * Copies the 7-entry sub-item id table from data_ov008_0208e958 into a stack
 * buffer, records the current mode/flag state into the shared-context status
 * halfword (+0x5c6 bits 0/1/3), and toggles the two action entries: 0x94 (shown
 * only when an action is available - gated on the cursor record byte[3], the input
 * branch func_ov008_0204ed3c ? func_ov008_020570c0 : func_ov008_0204ebf0, and the
 * busy gates +0x5c6 bit5 / func_ov008_0206f78c / func_ov008_0206f824) and 0x93.
 * If the state changed (or +0x5c6 bit 8 is still set), it rebuilds the 7 sub-item
 * enable flags from game progression - all-on when flag 0x200c is set; otherwise
 * from the day counter (GameState_GetField(0,9)) and per-item flags - stamps a
 * callback (func_ov008_02059698) at ctx+0x4a50, pushes each flag to entries
 * 0x65..0x6b (func_ov008_02054b18), and repositions the selector at the chosen
 * sub-item.
 *
 * Codegen notes:
 *  - `unsigned int flags[7] = {0};` (array initialiser) is what makes mwcc zero the
 *    stack flags with a HELD base pointer (add rX,sp,#0x1c; str) matching the ROM;
 *    zeroing them with 7 explicit `flags[i] = 0;` assignments instead uses direct
 *    [sp,#N] offsets and drops the base-pointer instruction (one byte short).
 *  - +0x5c6 accesses are 16-bit bitfields; ctx+0x5c8 uses array indexing
 *    (((unsigned int *)ctx)[0x172]) so mwcc emits the ldr/str offset, not an add.
 *  - The bVar4 input branch is `ed3c != 0 ? 570c0 : ebf0` (ROM beq to the ebf0 arm)
 *    and the entry-0x93 visibility normalises `ebf0() != 0` into bVar4 before the
 *    FindEntryById, matching the ROM's early movne/moveq.
 *  - func_ov008_02057b7c (the selector) is called K&R-style so the tail can pass 2
 *    args sharing uVar13; func_ov008_0205477c takes (ctx, callback-pointer).
 */

typedef struct {
    unsigned short b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1,
                   b8:1, b9:1, b10:1, b11:1, b12:1, b13:1, b14:1, b15:1;
} Flags;
typedef struct { unsigned int w[7]; } W7;

extern int func_ov008_0204ed3c(void);
extern int func_02023588(int flag);
extern int func_02030788(void);
extern int func_ov008_0204ecd8(int slot);
extern int func_ov008_0204ebf0(void);
extern int func_ov008_020570c0(void);
extern int func_ov008_0206f78c(void);
extern int func_ov008_0206f824(void);
extern int func_ov008_02050c54(void);
extern int func_ov008_02054788(int ui, int id);
extern int func_ov008_02054810(int ui, int entry);
extern void func_ov008_02054ba4(int ui, int entry, int visible);
extern void func_ov008_02054c44(int ui, int entry);
extern void func_ov008_0205477c(int ui, int val);
extern int func_ov008_020512b0(void);
extern int func_ov008_020547d8(int ui);
extern void func_ov008_02054cc4(int ui, int entry);
extern void func_ov008_02054b18(int ui, int entry, int val);
extern void func_ov008_02057b7c();
extern void func_ov008_02057ac4(int ctx);
extern int func_020235d0(int a, int b);
extern int func_ov008_02079264(int a);
extern void func_ov008_02059698(void);
extern int data_ov008_0208e958;
extern int data_ov008_02090f1c;

void func_ov008_02057f58(void)
{
    unsigned int flags[7] = {0};
    unsigned int values[7];
    int ctxp;
    int ui;
    unsigned short sVar1;
    unsigned short sVar2;
    int bVar4;
    int e;
    unsigned int uVar13;
    int i;

    *(W7 *)values = *(W7 *)&data_ov008_0208e958;
    ctxp = data_ov008_02090f1c;
    if (ctxp == 0) return;

    sVar1 = *(unsigned short *)(ctxp + 0x5c6);
    ((Flags *)(data_ov008_02090f1c + 0x5c6))->b0 = func_ov008_0204ed3c();
    ((Flags *)(data_ov008_02090f1c + 0x5c6))->b1 = func_02023588(0x200b);
    ((Flags *)(data_ov008_02090f1c + 0x5c6))->b3 = func_02023588(0x200c);
    sVar2 = *(unsigned short *)(data_ov008_02090f1c + 0x5c6);

    ui = func_ov008_02050c54();
    e = func_ov008_0204ecd8(func_02030788());
    bVar4 = 0;
    if (*(unsigned char *)(e + 3) != 8) {
        if (func_ov008_0204ed3c() != 0) bVar4 = func_ov008_020570c0();
        else bVar4 = func_ov008_0204ebf0();
    }
    if (((Flags *)(data_ov008_02090f1c + 0x5c6))->b5) bVar4 = 0;
    if (func_ov008_0206f78c() != 0) bVar4 = 0;
    if (func_ov008_0206f824()) bVar4 = 0;
    if (bVar4 != 0) {
        e = func_ov008_02054788(ui, 0x94);
        if (func_ov008_02054810(ui, e) == 0) {
            e = func_ov008_02054788(ui, 0x94);
            func_ov008_02054ba4(ui, e, 1);
            e = func_ov008_02054788(ui, 0x94);
            func_ov008_02054c44(ui, e);
        }
    } else {
        e = func_ov008_02054788(ui, 0x94);
        if (func_ov008_02054810(ui, e) != 0) {
            e = func_ov008_02054788(ui, 0x94);
            func_ov008_02054ba4(ui, e, 0);
        }
    }
    bVar4 = func_ov008_0204ebf0() != 0;
    e = func_ov008_02054788(ui, 0x93);
    func_ov008_02054ba4(ui, e, bVar4);

    if (sVar1 == sVar2 && ((Flags *)(data_ov008_02090f1c + 0x5c6))->b8 == 0) return;
    *(unsigned short *)(data_ov008_02090f1c + 0x5c6) &= ~0x100;

    if (func_02023588(0x200c) != 0) {
        func_ov008_0205477c(ui, 0);
        i = 0;
        do { flags[i] = 1; i = i + 1; } while (i < 7);
    } else {
        if (((Flags *)(data_ov008_02090f1c + 0x5c6))->b5) {
            func_ov008_0205477c(ui, (int)func_ov008_02059698);
            i = 0;
            do { flags[i] = 1; i = i + 1; } while (i < 7);
        } else {
            func_ov008_0205477c(ui, (int)func_ov008_02059698);
            i = 0;
            do { flags[i] = 0; i = i + 1; } while (i < 7);
            if (((Flags *)(data_ov008_02090f1c + 0x5c6))->b4) {
                flags[0] = 1;
                flags[1] = 1;
                flags[2] = 1;
                flags[3] = 1;
                flags[4] = 1;
            } else {
                if (func_ov008_0204ed3c() == 0) flags[0] = 1;
            }
            if (func_02023588(0x200b) != 0) {
                flags[5] = 1;
            } else {
                int day = func_020235d0(0, 9);
                int base = func_ov008_02079264(0xb);
                if (day < 0xb) flags[1] = 1;
                if (day <= 0x1a && func_02023588(base + 0x3c2b) == 0) flags[2] = 1;
            }
        }
    }

    if (func_ov008_020512b0()) return;

    uVar13 = ((unsigned int *)data_ov008_02090f1c)[0x172];
    if (uVar13 != 0xffffffff) {
        ((unsigned int *)data_ov008_02090f1c)[0x172] = 0xffffffff;
    } else {
        e = func_ov008_020547d8(ui);
        uVar13 = 0xffffffff;
        if (e != 0) {
            unsigned int key = *(unsigned int *)(e + 0xc);
            i = 0;
            do {
                if (key == values[i]) {
                    if (flags[i] == 0) uVar13 = values[i];
                    break;
                }
                i = i + 1;
            } while (i < 7);
        }
        if ((int)uVar13 < 0) {
            i = 0;
            do {
                if (flags[i] == 0) { uVar13 = values[i]; break; }
                i = i + 1;
            } while (i < 7);
        }
    }

    if (((Flags *)(data_ov008_02090f1c + 0x5c6))->b5 == 0) {
        e = func_ov008_02054788(ui, 9);
        func_ov008_02054cc4(ui, e);
        *(int *)(data_ov008_02090f1c + 0x88) = 9;
    }
    e = func_ov008_02054788(ui, 0x65); func_ov008_02054b18(ui, e, flags[0]);
    e = func_ov008_02054788(ui, 0x66); func_ov008_02054b18(ui, e, flags[1]);
    e = func_ov008_02054788(ui, 0x67); func_ov008_02054b18(ui, e, flags[2]);
    e = func_ov008_02054788(ui, 0x68); func_ov008_02054b18(ui, e, flags[3]);
    e = func_ov008_02054788(ui, 0x69); func_ov008_02054b18(ui, e, flags[4]);
    e = func_ov008_02054788(ui, 0x6a); func_ov008_02054b18(ui, e, flags[5]);
    e = func_ov008_02054788(ui, 0x6b); func_ov008_02054b18(ui, e, flags[6]);

    if (((Flags *)(data_ov008_02090f1c + 0x5c6))->b5 == 0) {
        if (uVar13 != 0xffffffff) {
            func_ov008_02057b7c(1, uVar13);
            func_ov008_02057ac4(data_ov008_02090f1c);
        } else {
            func_ov008_02057b7c(0, uVar13);
            func_ov008_02057ac4(data_ov008_02090f1c);
        }
    }
}
