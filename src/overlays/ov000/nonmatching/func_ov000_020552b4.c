/* UPDATE 2026-07-18 -- 44 -> 41 differing bytes. The `&` operand ORDER was wrong.
 * The ROM reads the GLOBAL first (`ldr r2,[pc]; ldrh r3,[r2]`) and the nav field second;
 * the old source had `nav->dirs & data_0204c18c`, which emitted the two ldrh the other way
 * round and mis-scheduled everything downstream. Now written `data_0204c18c & nav->dirs`
 * and the load order matches.
 *
 * What remains is a pure r1<->r2 PERMUTATION over the whole body (the ROM keeps the nav base
 * in r1 and reuses r2 for the pool address then the field value; mwcc does the mirror image).
 * Ruled out on top of the older list below:
 *   - all 24 declaration orders of the four locals (cur / n / dirs / cb), scripted;
 *   - hoisting the NavState pointer into a local -- that is WORSE, 636 vs 656: mwcc then
 *     reuses the pointer while the ROM recomputes `add rN, r5, #0x4a00` at every use.
 *     The ROM's redundant recomputation is a fact about the source, so keep the inline form.
 *
 * ⚠ CORRECTION to a claim made the same day in the skill's state.md: this function was flagged
 * as "missing four compound conditions" because a ranking tool's ROM-only list showed
 * `cmp r3,r0 ; ldrne r0,[r2,#0xa70] ; cmpne r3,r0` four times. That was wrong -- those
 * instructions appear on BOTH sides with the registers permuted. An alignment diff lists an
 * instruction as one-sided whenever the register fields differ, so never read the ROM-only
 * list without the mine-only list beside it.
 */
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
 * ★ UNFINISHED -- NOT a proven tie. **656/656 bytes, instruction stream IDENTICAL**, 39 operand
 * differences and no structural ones. It is a scratch-register permutation and nothing else.
 *
 * Register map: cur=r0, n=r1, keys=r4, self=r5 -- so r2/r3 are the only scratch. The ROM gives
 * navbase r1 (n's future register, still free there) and the mask value r3; mwcc gives navbase r3
 * and the mask value r1. Same swap recurs at every address-base/loaded-value pair.
 *
 * RULED OUT 2026-07-17 -- do not spend time re-testing these, every one is byte-identical to the
 * current file (all 656 B, all 39 diffs):
 *   - flipping the `&` operands (mwcc canonicalises commutative operands -- the source order of
 *     the two loads is NOT what picks the registers);
 *   - `volatile` on the mask, on `dirs`, and both, with and without the flip -- changes NOTHING,
 *     not even the load order, which is the strongest evidence that this statement's source form
 *     is not the lever;
 *   - the reset written as `!(x & y)`, as `!= 0` with an empty then-branch, as a ternary;
 *   - the mask via a local, `dirs` via a local, both via locals, in either order;
 *   - the mask declared `int`, or as `data_0204c18c[0]`;
 *   - ALL 24 declaration orders of cur/n/dirs/cb -- inert here (it is not a universal lever; it
 *     also did nothing for func_ov000_02056354).
 * PROVEN WRONG, so keep the current spelling: holding `Screen *`/`NavState *` in pointer VARIABLES
 * drops it to 592 B -- mwcc then parks them in callee-saved registers and stops rematerialising
 * the `add rX, r5, #0x4000` at each use. The inline casts are what the ROM does.
 *
 * Semantics and structure are settled -- do not re-derive them. 6-member family
 * (ov000/005/008/009/025/026), so it is worth 6 if it ever falls. */

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

    if ((data_0204c18c & ((NavState *)(self + 0x4a00))->dirs) == 0) {
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
