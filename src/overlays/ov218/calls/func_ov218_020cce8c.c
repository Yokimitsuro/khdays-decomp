/* Kick the 0/1 animation, set +0x14, then dispatch via c634. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov218_020ccec8(int);
void func_ov218_020cce8c(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)owner, 0, 1);
    *(int *)(owner + 0x14) = 0x1000;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov218_020ccec8);
}
