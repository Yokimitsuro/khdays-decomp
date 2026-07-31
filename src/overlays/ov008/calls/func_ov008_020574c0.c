/*
 * Ov008_Menu_RefreshSlotPanel - per-frame refresh of the 4 party/panel slots and
 * the selection/session state, one of the two setup steps run when the menu ticks.
 *
 * Builds the "active slots" mask (enabled & not-disabled, 4 bits), reconciles the
 * shared-context status halfword (+0x5c6) with the current mode/selection, and then
 * shows or hides the three UI entries per slot (ids slot+0x6f / +0x79 / +0x83):
 *   - Mode active (func_ov008_0204ed3c): while game flag 0x200c is set, clears bit 2
 *     of each cursor record's byte[2] for slots 1..3.
 *   - Mode inactive: mirrors func_ov008_0204ebf0 into +0x5c6 bit 2, and while flag
 *     0x200c is set plays the confirm/deny sound, latches +0x5c6 bit 8, dispatches
 *     handler 0x200c, refreshes button 5 and primes sub-scene 0 when the cursor
 *     record's byte[3] == 8.
 *   - When not busy (func_ov008_0207baf8) and +0x5c6 bit 4 is clear, a session-state
 *     change (mask != prev, or session inactive/other) primes sub-scene 0, dispatches
 *     handlers 0x200c and 0x200a, and latches +0x5c6 bits 8 and 4.
 * For each visible slot it re-shows and re-acquires the three entries and stamps the
 * icon rows from the slot's page (func_ov008_020571ac) and its record byte[3]
 * (func_ov008_020572b8 = Ov008_PageToIconRow); invisible slots are hidden.
 *
 * Codegen notes (this is a 1256-byte, all-callee-saved dispatcher):
 *  - +0x5c6 bit reads/writes are 16-bit bitfields (Flags); the per-record byte[2]
 *    bit-2 tests are byte bitfields (BFlags ->c2 == 1); byte[3] loads are unsigned.
 *  - The Session-state booleans are PREDICATED (`if (cond) x = 1;` statements), not
 *    `||` chains, matching the ROM's moveq/movne stream.
 *  - The slot loop tests `(mask & bit) != 0` with the VISIBLE branch as fall-through
 *    (so mwcc caches &stk in fp for the whole loop, not the constant 0).
 *  - `mask` is computed in two steps (load into mask, then AND) so it colours into
 *    the high callee-saved register the ROM uses; and in the slot loop `bVar2` is
 *    declared before `page` so the two byte loads colour r7/r8 as the ROM does.
 */

typedef struct {
    unsigned short b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1,
                   b8:1, b9:1, b10:1, b11:1, b12:1, b13:1, b14:1, b15:1;
} Flags;
typedef struct { unsigned char c0:1, c1:1, c2:1, c3:1, c4:1, c5:1, c6:1, c7:1; } BFlags;

extern int func_ov008_02050c54(void);
extern unsigned int func_ov008_0204ed98(void);
extern unsigned int func_ov008_0204eddc(int a);
extern unsigned int func_ov008_0204ec18(void);
extern int func_ov008_0204ed3c(void);
extern int func_02023588(int flag);
extern int func_ov008_0204ecd8(int slot);
extern int func_ov008_0204ebf0(void);
extern int func_02030788(void);
extern int func_ov008_0204ed20(void);
extern void func_02033b78(int a, int b);
extern void func_020235bc(int id);
extern void func_ov008_0206f7b0(int a);
extern void func_ov008_02050ab8(int a);
extern void func_ov008_0205714c(int a);
extern int func_ov008_0207baf8(void);
extern int func_02030640(void);
extern int func_02030670(void);
extern int func_020306b4(void);
extern void func_ov008_0204ebbc(int a);
extern void func_ov008_0207b960(int idx, void *out);
extern int func_ov008_020573c0(int a);
extern int func_ov008_02054788(int ctx, int id);
extern void func_ov008_02054ba4(int ctx, int entry, int visible);
extern void func_ov008_02054c08(int ctx, int entry);
extern void func_ov008_02054c80(int ctx, int entry, int value);
extern unsigned int func_ov008_020571ac(int a);
extern unsigned int func_ov008_020572b8(int a);
extern int data_ov008_02090f1c;

void func_ov008_020574c0(void)
{
    int ctx;
    unsigned int uVar7;
    unsigned int uVar8;
    unsigned int mask;
    int cur;
    int bVar3;
    int i;
    int entry;
    unsigned int stk[2];

    ctx = func_ov008_02050c54();
    uVar7 = func_ov008_0204ed98();
    uVar8 = func_ov008_0204eddc(7);
    mask = func_ov008_0204ec18();
    mask = (unsigned short)(~uVar8 & mask);

    if (func_ov008_0204ed3c() != 0) {
        if (func_02023588(0x200c) != 0) {
            i = 1;
            do {
                cur = func_ov008_0204ecd8(i);
                i = i + 1;
                if (cur != 0) *(unsigned char *)(cur + 2) &= ~4;
            } while (i < 4);
        }
    } else {
        int bit2 = ((Flags *)(data_ov008_02090f1c + 0x5c6))->b2;
        int uVar12 = func_ov008_0204ebf0();
        if (uVar12 != 0 && bit2 == 0) {
            ((Flags *)(data_ov008_02090f1c + 0x5c6))->b2 = uVar12;
        } else if (uVar12 == 0 && bit2 != 0) {
            ((Flags *)(data_ov008_02090f1c + 0x5c6))->b2 = uVar12;
        }
        if (func_02023588(0x200c) != 0) {
            int pi = func_02030788();
            int p1 = func_ov008_0204ed20();
            int p2 = func_ov008_0204ecd8(pi);
            bVar3 = 0;
            if (((BFlags *)(p1 + 2))->c2 == 1 && ((BFlags *)(p2 + 2))->c2 == 1) {
                func_02033b78(0, 3);
                bVar3 = 1;
            } else if (*(unsigned char *)(p1 + 3) != 8 && *(unsigned char *)(p2 + 3) != 8) {
                func_02033b78(0, 3);
                bVar3 = 1;
            }
            if (uVar12 == 0 && bit2 != 0) bVar3 = 1;
            if (bVar3) {
                *(unsigned short *)(data_ov008_02090f1c + 0x5c6) |= 0x100;
                func_020235bc(0x200c);
                func_ov008_0206f7b0(1);
                func_ov008_02050ab8(1);
                if (*(unsigned char *)(p1 + 3) == 8) {
                    *(unsigned char *)(p1 + 2) &= ~4;
                    func_ov008_0205714c(0);
                }
            }
        }
    }

    if (func_ov008_0207baf8() == 0 && ((Flags *)(data_ov008_02090f1c + 0x5c6))->b4 == 0) {
        int bVar13;
        int keep;
        bVar13 = 0;
        keep = 0;
        if (!func_02030640()) bVar13 = 1;
        if (mask != uVar7) bVar13 = 1;
        if (func_02030640()) {
            if (!func_02030670()) bVar13 = 1;
            if (func_020306b4() != 0) { bVar13 = 1; keep = bVar13; }
        }
        if (bVar13) {
            if (func_02023588(0x200c) != 0) {
                func_ov008_0205714c(0);
            }
            func_020235bc(0x200c);
            func_020235bc(0x200a);
            func_ov008_0204ebbc(0);
            func_ov008_0206f7b0(1);
            func_ov008_02050ab8(1);
            if (func_ov008_0204ed3c() != 0) {
                *(unsigned short *)(data_ov008_02090f1c + 0x5c6) |= 0x100;
                *(unsigned short *)(data_ov008_02090f1c + 0x5c6) |= 0x10;
            } else {
                if (keep) mask = 0;
                *(unsigned short *)(data_ov008_02090f1c + 0x5c6) |= 0x100;
                *(unsigned short *)(data_ov008_02090f1c + 0x5c6) |= 0x10;
            }
        }
    }

    i = 0;
    do {
        if ((mask & (1 << i)) != 0) {
            cur = func_ov008_0204ecd8(i);
            func_ov008_0207b960(i, stk);
            if (cur != 0) {
                int bVar2;
                int page = ((unsigned char *)stk)[5];
                bVar2 = *(unsigned char *)(cur + 3);
                if (func_ov008_020573c0(page) == 0) page = 0x14;
                if (bVar2 < 0) bVar2 = 0;
                entry = func_ov008_02054788(ctx, i + 0x6f);
                func_ov008_02054ba4(ctx, entry, 1);
                entry = func_ov008_02054788(ctx, i + 0x79);
                func_ov008_02054ba4(ctx, entry, 1);
                entry = func_ov008_02054788(ctx, i + 0x83);
                func_ov008_02054ba4(ctx, entry, 1);
                entry = func_ov008_02054788(ctx, i + 0x6f);
                func_ov008_02054c08(ctx, entry);
                entry = func_ov008_02054788(ctx, i + 0x79);
                func_ov008_02054c08(ctx, entry);
                entry = func_ov008_02054788(ctx, i + 0x83);
                func_ov008_02054c08(ctx, entry);
                entry = func_ov008_02054788(ctx, i + 0x6f);
                func_ov008_02054c80(ctx, entry, func_ov008_020571ac(page) & 0xffff);
                entry = func_ov008_02054788(ctx, i + 0x83);
                func_ov008_02054c80(ctx, entry, func_ov008_020572b8(bVar2) & 0xffff);
            }
        } else {
            entry = func_ov008_02054788(ctx, i + 0x6f);
            func_ov008_02054ba4(ctx, entry, 0);
            entry = func_ov008_02054788(ctx, i + 0x79);
            func_ov008_02054ba4(ctx, entry, 0);
            entry = func_ov008_02054788(ctx, i + 0x83);
            func_ov008_02054ba4(ctx, entry, 0);
        }
        i = i + 1;
    } while (i < 4);
}
