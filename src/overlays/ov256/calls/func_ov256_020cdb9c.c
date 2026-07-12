/* Kick the primary anim 0x1e and the +0x450 sub-anim 0xf, then dispatch via c634. */
extern int func_ov107_020c9264(int, int, int);
extern int func_ov107_020c9ee8(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov256_020cdbe4(int);
void func_ov256_020cdb9c(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)owner, 0x1e, 0);
    func_ov107_020c9ee8(*(int *)(*(int *)owner + 0x450), 0xf, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov256_020cdbe4);
}
