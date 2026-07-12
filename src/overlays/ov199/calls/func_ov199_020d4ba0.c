/* Kick the 1/0 animation, set +0x40, then dispatch via c634. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov199_020d4bdc(int);
void func_ov199_020d4ba0(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)owner, 1, 0);
    *(int *)(owner + 0x40) = 0x2000;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov199_020d4bdc);
}
