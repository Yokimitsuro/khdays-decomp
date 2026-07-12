/* Kick anim 0xb, arm the 020c5af8 timer, prime fields, then dispatch. */
extern int func_ov107_020c9264(int, int, int);
extern int func_ov107_020c5af8(int, int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov237_020cf048(int);
void func_ov237_020cefe4(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)owner, 0xb, 0);
    func_ov107_020c5af8(*(int *)owner, 0x12d, 6, *(int *)(owner + 0x38));
    *(int *)(owner + 0x30) = 0;
    *(signed char *)(owner + 0x55) = 2;
    *(signed char *)(*(int *)owner + 0x49c) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov237_020cf048);
}
