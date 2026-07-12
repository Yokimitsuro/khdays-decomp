/* Kick anim 6, clear +0x70/+0x7b, then dispatch via c634. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov260_020cfbec(int);
void func_ov260_020cfbac(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)owner, 6, 0);
    *(int *)(owner + 0x70) = 0;
    *(signed char *)(owner + 0x7b) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov260_020cfbec);
}
