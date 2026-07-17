/* Drive the emitter's 5-state machine (x4: ov041 + 3 twins). Unless it is already idle (0)
 * or stopping (4), and the owner is neither busy (ov022_02095524) nor in mode 0x30, force it
 * to state 4 and retune. Then: 1 retunes with 0, advances to 2 and FALLS INTO state 2's
 * body; 2 polls and, once the poll reports done, retunes with 1 and advances to 3; 3 just
 * polls; 4 polls and goes idle when done. State 0 does nothing.
 *
 * NO `default:` AND NO `case 0:` -- that is the whole point, not an omission. State 0 and
 * anything above 4 fall through the jump table to the function's implicit end, which is why
 * the ROM's table slot for case 0 IS a bare `pop {r4,r5,r6,pc}` rather than a branch, and the
 * fall-through slot is another one. Writing `case 0: return;` and `default: return;`
 * explicitly makes mwcc emit branches to a shared epilogue instead: 304 B merged, 308 B
 * separate, against the ROM's 300. See codegen-cracks.md.
 *
 * The `case 1` -> `case 2` fall-through is likewise deliberate: what looks like a tail after
 * the switch is actually state 2's body. */
extern int func_ov022_02095524(void *p);
extern void func_0202accc(void *p, int a, void *b, int c);
extern void func_01fff774(void *p, int a, int b);
extern unsigned int func_0202a818(void *p, int a);

void func_ov041_020b40f8(int self, int *p, int p3) {
    if (*p != 0 && *p != 4 && func_ov022_02095524((void *)(self + 0x22f8)) == 0 &&
        *(int *)(self + 0x6bc) != 0x30) {
        *p = 4;
        func_0202accc((char *)p + 4, 2, (char *)p + 0xe4, 2);
        func_01fff774((char *)p + 4, 2, 2);
    }
    switch (*p) {
    case 1:
        func_0202accc((char *)p + 4, 2, (char *)p + 0xe4, 0);
        func_01fff774((char *)p + 4, 2, 0);
        *p = 2;
        /* fall through */
    case 2:
        if (func_0202a818((char *)p + 4, p3) == 0) {
            return;
        }
        func_0202accc((char *)p + 4, 2, (char *)p + 0xe4, 1);
        func_01fff774((char *)p + 4, 2, 1);
        *p = 3;
        return;
    case 3:
        func_0202a818((char *)p + 4, p3);
        return;
    case 4:
        if (func_0202a818((char *)p + 4, p3) != 0) {
            *p = 0;
        }
        return;
    }
}
