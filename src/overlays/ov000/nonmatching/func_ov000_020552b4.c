/* func_ov000_020552b4 -- directional navigation: walk the widget graph from the focused node in
 * whichever direction was pressed, and focus the first node that will take it.
 *
 * Each direction has its own link field on the node, and its own button bit:
 *   0x40 -> +0x88 · 0x80 -> +0x8c · 0x20 -> +0x90 · 0x10 -> +0x94
 * The halfword at self+0x4a78 remembers which directions are currently allowed; when it no longer
 * intersects the mask at data_0204c18c it is reset to 0xf0 (all four). A successful move sets it
 * to just the direction taken, so the next press has to come from the same axis.
 *
 * The walk skips nodes that are disabled (bit 0 of +0x84 set) or not focusable (bit 1 clear), and
 * gives up as soon as it reaches a node whose group at +0xc matches either the node it started
 * from or the currently focused one -- i.e. it will not wrap round inside the same group.
 *
 * Two callbacks close it out: +0x98 on the focused node fires on the accept button (bit 0), and
 * the screen-level handler at self+0x4a50 gets every press within the 0x2fff mask.
 *
 * The four blocks are written out because the ROM has them unrolled -- they differ only in the
 * link offset, the button bit and the value parked back in +0x4a78.
 *
 * ------------------------------------------------------------------------------------------
 * ★ UNFINISHED -- NOT a proven tie. Now at **656/656 bytes with the instruction stream identical**;
 * all that is left is a REGISTER PERMUTATION (39 operand differences, no structural ones).
 *
 * The 40 bytes it started at were the >0xfff offset splitting, and three things fixed that:
 *   - the two bases really are two structs, and modelling them is what keeps the ROM's split:
 *     `Screen` at self+0x4000 (ldr has a 12-bit offset, so +0xa50/+0xa70 reach from there) and
 *     `NavState` at self+0x4a00 (strh only has 8 bits, so it needs its own base for +0x78).
 *     Raw `*(u16 *)(self + 0x4a78)` makes mwcc materialise the whole address instead;
 *   - `dirs` read once after the 0xf0 reset and reused by all four tests (2 instructions each);
 *   - the accept callback loaded INSIDE its condition -- `(cb = *(...)(cur + 0x98)) != 0` gives
 *     the ROM's single `ldrne r1` / `cmpne` / `blx r1`; testing the field then calling through it
 *     reads it twice.
 *
 * What remains is r1/r2 swapped from the very first temporaries onward:
 *   ROM:  ldr r2,[pc] (&mask) ; add r1,r5,#0x4a00 (nav base)   -> dirs ends up in r2
 *   mine: ldr r1,[pc] (&mask) ; add r2,r5,#0x4a00              -> dirs ends up in r1
 * and everything cascades from there. Tried and rejected: flipping the `&` operands, `dirs` as
 * unsigned short vs int. These are scratch registers, so the declaration-order lever (which
 * governs r4..r8) does not reach them.
 *
 * Semantics and structure are settled -- do not re-derive them. This needs the r1/r2 coin-flip
 * only. */

typedef struct {
    unsigned disabled : 1;
    unsigned focusable : 1;
} NodeFlags;

/* The screen block sits at self+0x4000: ldr has a 12-bit offset, so mwcc reaches +0xa50/+0xa70
   from that base. The nav block below needs its own because strh only has 8 bits. */
typedef struct {
    char reserved[0xa50];
    void (*handler)(int, int);
    char reserved2[0x1c];
    int focused;
} Screen;

/* The nav block sits at self+0x4a00 and mwcc addresses it as base+0x78, because strh only has an
   8-bit offset. Modelling it as a struct is what keeps that split. */
typedef struct {
    char reserved[0x78];
    unsigned short dirs;
} NavState;

extern void func_ov000_02055d98(int self, int node);
extern unsigned short data_0204c18c;

void func_ov000_020552b4(int self, int keys) {
    int cur;
    int n;
    unsigned short dirs;
    void (*cb)(int);

    cur = ((Screen *)(self + 0x4000))->focused;
    if (cur == 0) {
        return;
    }

    if ((((NavState *)(self + 0x4a00))->dirs & data_0204c18c) == 0) {
        ((NavState *)(self + 0x4a00))->dirs = 0xf0;
    }
    /* Read ONCE, after the reset, and reused by all four tests -- that is what the ROM does
       (ldrh into r2, then four `tst r1,r2`). Re-reading the field per test costs 2 instructions
       each. */
    dirs = ((NavState *)(self + 0x4a00))->dirs;

    if ((keys & 0x40) & dirs) {
        n = *(int *)(cur + 0x88);
        if (n == 0) {
            goto tail;
        }
        for (;;) {
            if (*(int *)(n + 0xc) == *(int *)(cur + 0xc)
                || *(int *)(n + 0xc) == *(int *)(((Screen *)(self + 0x4000))->focused + 0xc)) {
                goto tail;
            }
            if (!((NodeFlags *)(n + 0x84))->disabled && ((NodeFlags *)(n + 0x84))->focusable) {
                func_ov000_02055d98(self, n);
                ((NavState *)(self + 0x4a00))->dirs = 0x40;
                goto tail;
            }
            cur = n;
            n = *(int *)(n + 0x88);
            if (n == 0) {
                goto tail;
            }
        }
    }

    if ((keys & 0x80) & dirs) {
        n = *(int *)(cur + 0x8c);
        if (n == 0) {
            goto tail;
        }
        for (;;) {
            if (*(int *)(n + 0xc) == *(int *)(cur + 0xc)
                || *(int *)(n + 0xc) == *(int *)(((Screen *)(self + 0x4000))->focused + 0xc)) {
                goto tail;
            }
            if (!((NodeFlags *)(n + 0x84))->disabled && ((NodeFlags *)(n + 0x84))->focusable) {
                func_ov000_02055d98(self, n);
                ((NavState *)(self + 0x4a00))->dirs = 0x80;
                goto tail;
            }
            cur = n;
            n = *(int *)(n + 0x8c);
            if (n == 0) {
                goto tail;
            }
        }
    }

    if ((keys & 0x20) & dirs) {
        n = *(int *)(cur + 0x90);
        if (n == 0) {
            goto tail;
        }
        for (;;) {
            if (*(int *)(n + 0xc) == *(int *)(cur + 0xc)
                || *(int *)(n + 0xc) == *(int *)(((Screen *)(self + 0x4000))->focused + 0xc)) {
                goto tail;
            }
            if (!((NodeFlags *)(n + 0x84))->disabled && ((NodeFlags *)(n + 0x84))->focusable) {
                func_ov000_02055d98(self, n);
                ((NavState *)(self + 0x4a00))->dirs = 0x20;
                goto tail;
            }
            cur = n;
            n = *(int *)(n + 0x90);
            if (n == 0) {
                goto tail;
            }
        }
    }

    if ((keys & 0x10) & dirs) {
        n = *(int *)(cur + 0x94);
        if (n == 0) {
            goto tail;
        }
        for (;;) {
            if (*(int *)(n + 0xc) == *(int *)(cur + 0xc)
                || *(int *)(n + 0xc) == *(int *)(((Screen *)(self + 0x4000))->focused + 0xc)) {
                goto tail;
            }
            if (!((NodeFlags *)(n + 0x84))->disabled && ((NodeFlags *)(n + 0x84))->focusable) {
                func_ov000_02055d98(self, n);
                ((NavState *)(self + 0x4a00))->dirs = 0x10;
                goto tail;
            }
            cur = n;
            n = *(int *)(n + 0x94);
            if (n == 0) {
                goto tail;
            }
        }
    }

    /* The callback is loaded INSIDE the condition, so it is read once (the ROM's `ldrne r1` /
     * `cmpne r1,#0` / `blx r1`); testing the field and then calling through it reads it twice. */
    if ((keys & 1) && (cb = *(void (**)(int))(cur + 0x98)) != 0) {
        cb(((Screen *)(self + 0x4000))->focused);
    }

tail:
    if (((Screen *)(self + 0x4000))->handler == 0) {
        return;
    }
    if ((keys & 0x2fff) == 0) {
        return;
    }
    ((Screen *)(self + 0x4000))->handler(((Screen *)(self + 0x4000))->focused, keys);
}
