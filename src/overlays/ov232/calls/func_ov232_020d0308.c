/* Feed the two sub-values at param_1+0x38c/+0x390 to func_ov107_020c2b38 with param_2, then
 * finalize via func_ov107_020c7c1c. */
extern void func_ov107_020c2b38(int a, int b);
extern void func_ov107_020c7c1c(int a, int b);
void func_ov232_020d0308(int param_1, int param_2) {
    int i;
    for (i = 0; i < 2; i++) {
        func_ov107_020c2b38(param_2, ((int *)param_1)[i + 0xe3]);
    }
    func_ov107_020c7c1c(param_1, param_2);
}
