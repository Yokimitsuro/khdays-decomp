/* Clear +0x6a, kick animation 0xa, then dispatch via c634. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov256_020cf738(int);
void func_ov256_020cf700(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(signed char *)(owner + 0x6a) = 0;
    func_ov107_020c9264(*(int *)owner, 0xa, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov256_020cf738);
}
