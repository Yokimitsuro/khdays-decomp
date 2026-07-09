/* NONMATCHING: register-coloring tie. Structure is byte-identical (76B) — the
 * count byte lands in a scratch reg and the return value in r1 in the original
 * (ldrb ip; mov r1,#1 ...) but mwcc colors them r1/r2 the other way. Tried
 * declaration reorder and for-vs-while loop; only the register numbers differ.
 * Semantics: returns 1 unless any of the n (=byte@+0x19) 0x1c8-stride slots
 * (base=*(arg0+0xc)) has a nonzero byte at +2. */
int func_ov022_020912d8(int arg0) {
    int r = 1;
    int n = *(unsigned char *)(arg0 + 0x19);
    int i;
    int e;
    if (n == 0) return r;
    e = *(int *)(arg0 + 0xc);
    for (i = 0; i < n; i++) {
        if (*(char *)(e + 2) != 0) { r = 0; break; }
        e += 0x1c8;
    }
    return r;
}
