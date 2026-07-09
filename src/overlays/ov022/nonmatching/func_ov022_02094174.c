/* NONMATCHING: predicate-vs-branch tie (twin of func_ov022_02093008). The
 * original predicates the guard return and result; mwcc branches the guard to an
 * out-of-line return-0 tail (+0 size but wrong bytes at the guard). Same 44B.
 * Semantics: returns 1 iff func_ov022_0209405c(arg0) is true AND *(int*)(arg0+0x110)>0. */
extern int func_ov022_0209405c(unsigned char *arg0);
int func_ov022_02094174(unsigned char *arg0) {
    return func_ov022_0209405c(arg0) && *(int *)(arg0 + 0x110) > 0;
}
