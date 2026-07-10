/* NONMATCHING: register-coloring tie, byte-exact structure. The original colors the
 * toggled value into r2 and the 0xC multiplier into r1; mwcc shifts both down one
 * (v->r1, const->r0), since r0 is free after the guard call returns. Seven source
 * forms tried (xor in place, int vs unsigned, node/addr temporaries, mla
 * association, pointer-typed param). Semantics are exact: double-buffer toggle. */
extern int func_01fffaf4(int *node);

void func_01fffac0(int p) {
    unsigned int v;
    if (func_01fffaf4(*(int **)(p + 0x18)) == 0) return;
    v = *(unsigned int *)(p + 0x1c) ^ 1;
    *(unsigned int *)(p + 0x1c) = v;
    *(unsigned int *)(p + 0x18) = v * 0xc + p;
}
