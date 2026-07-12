/* Tick +0x1c down; once expired clear the gate byte, and unless busy kick anim 0xa and dispatch. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov253_020ce310(int);
void func_ov253_020ce2a8(int param_1) {
    int a = *(int *)param_1;
    int owner = *(int *)(param_1 + 4);
    int t = *(int *)(owner + 0x1c) - *(int *)(a + 0x2c);
    *(int *)(owner + 0x1c) = t;
    if (t > 0) return;
    *(signed char *)(*(int *)(*(int *)owner + 0x38c) + 0xa8) = 0;
    if (*(unsigned char *)(*(int *)(owner + 4)) != 0) return;
    func_ov107_020c9264(*(int *)owner, 0xa, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov253_020ce310);
}
