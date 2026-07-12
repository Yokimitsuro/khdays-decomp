/* Kick the primary anim 0x20 and the +0x450 sub-anim 0x11, then dispatch via c634. */
extern int func_ov107_020c9264(int, int, int);
extern int func_ov107_020c9ee8(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov256_020cdf5c(int);
void func_ov256_020cdf14(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)owner, 0x20, 0);
    func_ov107_020c9ee8(*(int *)(*(int *)owner + 0x450), 0x11, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov256_020cdf5c);
}
