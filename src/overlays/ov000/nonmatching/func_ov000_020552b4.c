/* ** SUPERSEDED 2026-07-22: MATCHED, and the whole six-member family with it
 * (ov000, ov005, ov008, ov009, ov025, ov026). See staging/ov000/.
 *
 * THE LEVER: ONE struct for the WHOLE object, typed on the PARAMETER.
 *     void func_ov000_020552b4(Root *self, int keys)
 * with Root modelling the object from 0 to +0x4a78 in a single declaration
 * (0x4a50 handler, 0x4a70 focused, 0x4a78 dirs). Not two sub-block structs
 * (Screen at +0x4000, NavState at +0x4a00) reached through inline casts, which is
 * what this file did.
 *
 * ** WHY THE OLD NOTE MISSED IT, because the distinction is subtle and it will recur:
 * it recorded, correctly, that "holding Screen*/NavState* in pointer VARIABLES drops it
 * to 592 B -- mwcc parks them in callee-saved registers and stops rematerialising the
 * `add rX, r5, #0x4000` at each use", and concluded that the inline casts were therefore
 * what the ROM did. The measurement was right and the conclusion was wrong. A local
 * pointer variable and a typed parameter are not the same thing: the local is a value
 * mwcc can keep, while `self->focused` on a typed parameter is an address computation it
 * must redo, because the offsets exceed the 12-bit ldr immediate. The ROM's repeated
 * `add rN, r5, #0x4000` is a CONSEQUENCE of the offset range, not a source idiom to
 * imitate with casts.
 *
 * So: when sub-block offsets are too large for a single immediate, model the whole object
 * as one struct and type the parameter. Do not hand-split it into sub-structs, and do not
 * read "pointer locals make it worse" as "therefore inline casts are right".
 *
 * The 39-operand r1/r2 permutation this file spent three sessions on was entirely
 * downstream of that. Nothing about register allocation needed solving.
 */
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
