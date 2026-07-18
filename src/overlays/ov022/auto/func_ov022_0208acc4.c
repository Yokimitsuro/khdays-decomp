/* Clamp the "2" reaction to 1 for kind 10. The single-case switch is deliberate:
 * an `if (a == 10 && b == 2)` (or a nested if) lets mwcc if-convert BOTH tests into
 * a cmp/cmpeq chain (20 B); the switch keeps the ROM's real branch on the first
 * test and predicates only the second (24 B). */
int func_ov022_0208acc4(int arg0, int arg1) {
    switch (arg0) {
    case 10:
        if (arg1 == 2) arg1 = 1;
        break;
    }
    return arg1;
}
