/* NONMATCHING: predicate-vs-branch tie (same class as func_ov022_02093008). The
 * original predicates the short-circuit guard (bl; cmp; moveq r0,#0; popeq) and
 * result; mwcc branches (beq) to an out-of-line return-0 tail. Same logic (44B
 * predicated vs 48B branched). Returns 1 iff func_02030694() AND (*arg0 & 0x100). */
extern int func_02030694(void);
int func_ov022_02090308(unsigned short *arg0) {
    return func_02030694() && (*arg0 & 0x100) != 0;
}
