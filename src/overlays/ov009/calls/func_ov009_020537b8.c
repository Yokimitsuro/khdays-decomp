/* The single-case switch is deliberate: two plain `if (...) return;` guards let mwcc
 * if-convert the second into the first (ldreq/cmpeq, 8 B short). The ROM emits two
 * separate `popne {r3,pc}` early returns, and the switch is what reproduces that. */
extern void func_ov009_02052b58(int obj, int old_value, int new_value);
extern void func_02033b78(int a, int b);

void func_ov009_020537b8(int param_1) {
    int old = *(int *)param_1;
    int nv;
    switch (*(int *)(param_1 + 0x240)) {
    case 0:
        if (*(int *)(param_1 + 8) != 0) return;
        nv = old + 1;
        *(int *)param_1 = nv;
        if (nv >= 3) {
            *(int *)param_1 = 0;
        }
        func_ov009_02052b58(param_1, old, *(int *)param_1);
        func_02033b78(0, 0);
        break;
    }
}
