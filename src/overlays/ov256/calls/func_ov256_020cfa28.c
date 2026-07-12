/* Run 020ccd54, reset fields, kick anim 0xf, then dispatch via c634. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov256_020ccd54(int);
extern int func_ov256_020cfa70(int);
void func_ov256_020cfa28(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov256_020ccd54(param_1);
    *(int *)(owner + 0x4c) = 0;
    *(signed char *)(owner + 0x6a) = 0;
    *(signed char *)(owner + 0x69) = 1;
    func_ov107_020c9264(*(int *)owner, 0xf, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov256_020cfa70);
}
