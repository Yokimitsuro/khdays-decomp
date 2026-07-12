/* Clear +0x64/+0x94, kick the idle animation, then dispatch via c634. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov252_020d0334(int);
void func_ov252_020d02f8(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(int *)(owner + 0x64) = 0;
    *(signed char *)(owner + 0x94) = 0;
    func_ov107_020c9264(*(int *)owner, 0, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov252_020d0334);
}
