/* The single-case switch is deliberate: two plain `if (...) return;` guards let mwcc
 * if-convert the second into the first (ldreq/cmpeq, 4 B short). The ROM emits two
 * separate `popne {r3,pc}` early returns, and the switch is what reproduces that. */
extern void func_ov008_02067970(int obj, int old_value, int new_value);
extern void func_02033b78(int a, int b);

void func_ov008_020685d0(int param_1) {
    int old = *(int *)param_1;
    int nv;
    switch (*(int *)(param_1 + 0x23c)) {
    case 0:
        if (*(int *)(param_1 + 4) != 0) return;
        nv = old + 1;
        *(int *)param_1 = nv;
        if (nv >= 3) {
            *(int *)param_1 = 0;
        }
        func_ov008_02067970(param_1, old, *(int *)param_1);
        func_02033b78(0, 0);
        break;
    }
}
