/* Prime the fields, kick anim 0xd, notify 020cd524, then dispatch via c634. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov259_020cd524(int, int, int);
extern int func_ov259_020ce9e0(int);
void func_ov259_020ce988(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(signed char *)(owner + 0xac) = 0;
    *(int *)(owner + 0x94) = 0xb4;
    *(int *)(owner + 0x58) = 1;
    func_ov107_020c9264(*(int *)owner, 0xd, 0);
    func_ov259_020cd524(param_1, 0xd, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov259_020ce9e0);
}
