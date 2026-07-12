/* Clear +0x54/+0x4c, set +0x69, kick anim 0x19, then dispatch via c634. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov256_020cfed0(int);
void func_ov256_020cfe8c(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(int *)(owner + 0x54) = 0;
    *(int *)(owner + 0x4c) = 0;
    *(signed char *)(owner + 0x69) = 1;
    func_ov107_020c9264(*(int *)owner, 0x19, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov256_020cfed0);
}
