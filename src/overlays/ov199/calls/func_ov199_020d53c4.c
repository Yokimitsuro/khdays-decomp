/* Kick anim 2, run 020d4234, then dispatch via c634. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov199_020d4234(int, int);
extern int func_ov199_020d5404(int);
void func_ov199_020d53c4(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)owner, 2, 0);
    func_ov199_020d4234(*(int *)owner, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov199_020d5404);
}
