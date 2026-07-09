/* NONMATCHING: mwcc predicates the short `&&` (cmp;cmpeq;moveq, 20B) where the
 * original branches (cmp;bne;cmp;moveq, 24B). Tried nested-if and goto; mwcc
 * always predicates a body this short. Byte-exact in the blob; C below is
 * semantically exact and readable. */
int func_ov022_0208acc4(int arg0, int arg1) {
    if (arg0 == 10 && arg1 == 2) arg1 = 1;
    return arg1;
}
