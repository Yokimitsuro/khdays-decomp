/* NONMATCHING: predicate-vs-branch tie. The original predicates the short-circuit
 * guard return (bl; cmp; moveq r0,#0; popeq) and the boolean result (moveq r0,#1;
 * movne r0,#0) with no branch; mwcc branches the guard (beq) to an out-of-line
 * return-0 tail. Same size (44B), same logic. Tried &&, if(!x)return 0, and
 * if(x)return..;return 0 — all branch the constant-0 guard path.
 * Semantics: returns 1 iff func_ov022_02092ff0(arg0) is true AND *(int*)(arg0+0x958)==0. */
extern int func_ov022_02092ff0(unsigned char *arg0);
int func_ov022_02093008(unsigned char *arg0) {
    return func_ov022_02092ff0(arg0) && *(int *)(arg0 + 0x958) == 0;
}
