/* Bind param_2 to the main sub-object at (param_1)+0x3dc and to the two 8-entry sub-object
 * arrays at +0x3e0 and +0x3e4, then run the ov107 attach for the pair. */
extern void func_ov107_020c2b38(int a, int b);
extern void func_ov107_020c7c1c(int a, int b);
void func_ov213_020cccc0(int param_1, int param_2) {
    int i;
    func_ov107_020c2b38(param_2, *(int *)(param_1 + 0x3dc));
    for (i = 0; i < 8; i++) {
        func_ov107_020c2b38(param_2, ((int *)*(int *)(param_1 + 0x3e0))[i]);
    }
    for (i = 0; i < 8; i++) {
        func_ov107_020c2b38(param_2, ((int *)*(int *)(param_1 + 0x3e4))[i]);
    }
    func_ov107_020c7c1c(param_1, param_2);
}
