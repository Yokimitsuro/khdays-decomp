/* NONMATCHING: predicate-vs-branch tie. The original fully predicates the &&
 * cascade and the guard-fail return (cmp;ldrheq;cmpeq;...;movne r0,#0;bxne),
 * mwcc branches (bne) to a shared return-0 tail (+4B). Splitting into early
 * returns makes it much worse (96B). Structure/logic identical otherwise.
 * Semantics: if node@arg0 has field4==0xfeff, field_c==0x10, field_e==1, follow
 * the *(arg0+0x10) sub-pointer; return its byte@+9 when byte@+8==0, else 0. */
unsigned char func_ov022_020b1078(int arg0) {
    if (arg0 == 0) return 0;
    if (*(unsigned short *)(arg0 + 4) == 0xfeff &&
        *(unsigned short *)(arg0 + 0xc) == 0x10 &&
        *(unsigned short *)(arg0 + 0xe) == 1) {
        int e = arg0 + *(int *)(arg0 + 0x10);
        if (*(unsigned char *)(e + 8) == 0) return *(unsigned char *)(e + 9);
        return 0;
    }
    return 0;
}
