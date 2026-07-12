/* Feed the two sub-values at param_1+0x38c/+0x390 to func_ov107_020c2b20 with param_2, then
 * finalize via func_ov107_020c7b70. */
extern void func_ov107_020c2b20(int a, int b);
extern void func_ov107_020c7b70(int a, int b);
void func_ov280_020d02d0(int param_1, int param_2) {
    int i;
    for (i = 0; i < 2; i++) {
        func_ov107_020c2b20(param_2, ((int *)param_1)[i + 0xe3]);
    }
    func_ov107_020c7b70(param_1, param_2);
}
