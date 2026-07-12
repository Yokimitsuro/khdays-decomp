/* Prime the fields, kick anim 8, notify 020cd524 and 020cd628, then dispatch. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov259_020cd524(int, int, int);
extern int func_ov259_020cd628(int, int, int);
extern int func_ov259_020cea80(int);
void func_ov259_020cea14(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(int *)(owner + 0x68) = 0;
    *(signed char *)(owner + 0xac) = 0;
    *(int *)(owner + 0x88) = 0xc00;
    *(int *)(owner + 0x94) = 0x1e;
    func_ov107_020c9264(*(int *)owner, 8, 0);
    func_ov259_020cd524(param_1, 8, 0);
    func_ov259_020cd628(param_1, 0x11, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov259_020cea80);
}
