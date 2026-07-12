/* Kick the 0x13/0 animation, set +0x54, then dispatch via c634. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov235_020cfb58(int);
void func_ov235_020cfb1c(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)owner, 0x13, 0);
    *(int *)(owner + 0x54) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov235_020cfb58);
}
