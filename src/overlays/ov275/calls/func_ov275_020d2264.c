/* Release any queued sub-request in the 5 slots at (param_1)+0x3e0 (second word non-zero),
 * clearing each as it is handled, then run the ov107 detach for the pair. */
extern void func_0203c650(int a, int b);
extern void func_ov107_020c7c1c(int a, int b);
struct row8_020cc804 { int p; int q; };
void func_ov275_020d2264(int param_1, int param_2) {
    int i;
    for (i = 0; i < 5; i++) {
        int q = ((struct row8_020cc804 *)*(int *)(param_1 + 0x3e0))[i].q;
        if (q != 0) {
            func_0203c650(*(int *)(param_1 + 0x3c), q);
            ((struct row8_020cc804 *)*(int *)(param_1 + 0x3e0))[i].q = 0;
        }
    }
    func_ov107_020c7c1c(param_1, param_2);
}
