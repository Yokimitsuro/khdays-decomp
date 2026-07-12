/* Kick the 5 animation on the object, then dispatch via c634. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov199_020d5150(int);
void func_ov199_020d511c(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)owner, 5, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov199_020d5150);
}
