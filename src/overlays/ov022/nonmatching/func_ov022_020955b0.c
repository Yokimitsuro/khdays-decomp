/* NONMATCHING: same dead-flag case as func_ov022_020ad1d0 — the original checks
 * `(field@+0x468 & FLAG) == 0` with FLAG a 0-valued build constant, so mwcc
 * emits an extra `ldr; and #0; cmp #0` we cannot reproduce (any literal & 0 is
 * folded). Clean equivalent below drops the always-true term. */
int func_ov022_020955b0(int arg0) {
    int t;
    if (*(int *)(arg0 + 4) != 10) return 0;
    t = *(int *)(*(int *)(arg0 + 0x328) + 0xc);
    if ((t == 5 || t == 10) &&
        (*(unsigned int *)(*(int *)(arg0 + 0x328) + 0x464) & 0x10000) != 0) {
        return 0;
    }
    return 1;
}
