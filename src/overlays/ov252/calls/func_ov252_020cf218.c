/* Set +0x98, kick the idle animation, then dispatch via c634. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov252_020cf254(int);
void func_ov252_020cf218(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(int *)(owner + 0x98) = 1;
    func_ov107_020c9264(*(int *)owner, 0, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov252_020cf254);
}
