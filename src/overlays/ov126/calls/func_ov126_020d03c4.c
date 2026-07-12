/* Bind param_2 to the two sub-objects at (param_1)+0x3a0[0..1], then run the ov107 attach. */
extern void func_ov107_020c2b38(int a, int b);
extern void func_ov107_020c7c1c(int a, int b);
void func_ov126_020d03c4(int param_1, int param_2) {
    int i;
    for (i = 0; i < 2; i++) {
        func_ov107_020c2b38(param_2, ((int *)param_1)[i + 0xe8]);
    }
    func_ov107_020c7c1c(param_1, param_2);
}
