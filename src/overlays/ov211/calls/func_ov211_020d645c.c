/* Unless the +4 field is set, register the handler. */
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov211_020d5ecc(int);
void func_ov211_020d645c(int param_1) {
    int child = *(int *)(param_1 + 4);
    if (*(int *)(child + 4) != 0) return;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov211_020d5ecc);
}
