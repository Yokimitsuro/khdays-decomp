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
 * ★ UNFINISHED -- this is NOT a proven tie, just where I ran out of time. 696 vs 656 bytes, and
 * the whole 40 is one steerable thing: how mwcc SPLITS the >0xfff offsets.
 *
 *   ROM:  add r1,r5,#0x4a00 ; ldrh r2,[r1,#0x78]     (base + the field as the load offset)
 *   mine: add r0,r5,#0x278 ; add r3,r0,#0x4800 ; strheq r0,[r3]   (full address, offset 0)
 *
 * The interesting part: mwcc splits it the ROM's way for the FIRST access (`cur = *(int *)(self +
 * 0x4a70)` gives `add r0,r5,#0x4000 ; ldr r0,[r0,#0xa70]`, byte-identical) and the wrong way for
 * the ones inside the loops, where it is a nested deref. So the lever exists; I have not found it.
 *
 * Things worth trying next, roughly in order:
 *   - model self+0x4000 / self+0x4a00 as real structs and access the fields through them, which
 *     is what the two bases look like (this is what fixed func_ov000_0205721c);
 *   - a `char *` base local for each (the catalog's "base beyond 0xfff" crack) -- note the ROM
 *     RE-COMPUTES `add rN,r5,#0x4a00` per use rather than hoisting, so a hoisted local may not be
 *     it;
 *   - a `char *self` parameter instead of int.
 * The `dirs` local is already right: the ROM reads self+0x4a78 once after the 0xf0 reset and
 * reuses it for all four tests. Semantics are settled; only the addressing is open. */

typedef struct {
    unsigned disabled : 1;
    unsigned focusable : 1;
} NodeFlags;

extern void func_ov000_02055d98(int self, int node);
extern unsigned short data_0204c18c;

void func_ov000_020552b4(int self, int keys) {
    int cur;
    int n;
    int dirs;

    cur = *(int *)(self + 0x4a70);
    if (cur == 0) {
        return;
    }

    if ((data_0204c18c & *(unsigned short *)(self + 0x4a78)) == 0) {
        *(unsigned short *)(self + 0x4a78) = 0xf0;
    }
    /* Read ONCE, after the reset, and reused by all four tests -- that is what the ROM does
       (ldrh into r2, then four `tst r1,r2`). Re-reading the field per test costs 2 instructions
       each. */
    dirs = *(unsigned short *)(self + 0x4a78);

    if ((keys & 0x40) & dirs) {
        n = *(int *)(cur + 0x88);
        if (n == 0) {
            goto tail;
        }
        for (;;) {
            if (*(int *)(n + 0xc) == *(int *)(cur + 0xc)
                || *(int *)(n + 0xc) == *(int *)(*(int *)(self + 0x4a70) + 0xc)) {
                goto tail;
            }
            if (!((NodeFlags *)(n + 0x84))->disabled && ((NodeFlags *)(n + 0x84))->focusable) {
                func_ov000_02055d98(self, n);
                *(unsigned short *)(self + 0x4a78) = 0x40;
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
                || *(int *)(n + 0xc) == *(int *)(*(int *)(self + 0x4a70) + 0xc)) {
                goto tail;
            }
            if (!((NodeFlags *)(n + 0x84))->disabled && ((NodeFlags *)(n + 0x84))->focusable) {
                func_ov000_02055d98(self, n);
                *(unsigned short *)(self + 0x4a78) = 0x80;
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
                || *(int *)(n + 0xc) == *(int *)(*(int *)(self + 0x4a70) + 0xc)) {
                goto tail;
            }
            if (!((NodeFlags *)(n + 0x84))->disabled && ((NodeFlags *)(n + 0x84))->focusable) {
                func_ov000_02055d98(self, n);
                *(unsigned short *)(self + 0x4a78) = 0x20;
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
                || *(int *)(n + 0xc) == *(int *)(*(int *)(self + 0x4a70) + 0xc)) {
                goto tail;
            }
            if (!((NodeFlags *)(n + 0x84))->disabled && ((NodeFlags *)(n + 0x84))->focusable) {
                func_ov000_02055d98(self, n);
                *(unsigned short *)(self + 0x4a78) = 0x10;
                goto tail;
            }
            cur = n;
            n = *(int *)(n + 0x94);
            if (n == 0) {
                goto tail;
            }
        }
    }

    if ((keys & 1) && *(int *)(cur + 0x98) != 0) {
        (*(void (**)(int))(cur + 0x98))(*(int *)(self + 0x4a70));
    }

tail:
    if (*(int *)(self + 0x4a50) == 0) {
        return;
    }
    if ((keys & 0x2fff) == 0) {
        return;
    }
    (*(void (**)(int, int))(self + 0x4a50))(*(int *)(self + 0x4a70), keys);
}
