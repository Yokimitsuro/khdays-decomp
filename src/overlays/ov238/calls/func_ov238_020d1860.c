/* Run 020d0878, reset the motion fields, then dispatch via c634. */
extern int func_0203c634(int, int, void *);
extern int func_ov238_020d0878(int);
extern int func_ov238_020d18a4(int);
void func_ov238_020d1860(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov238_020d0878(param_1);
    *(int *)(owner + 0x20) = 0;
    *(signed char *)(owner + 0x2d) = 0;
    *(signed char *)(owner + 0x2e) = 1;
    *(signed char *)(owner + 0x31) = 4;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov238_020d18a4);
}
