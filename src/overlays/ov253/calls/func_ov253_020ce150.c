/* Reset the motion fields, latch +0x454, kick anim 0xb, then dispatch via c634. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov253_020ce19c(int);
void func_ov253_020ce150(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(int *)(owner + 0x34) = 0;
    *(int *)(owner + 0x1c) = 0;
    *(signed char *)(owner + 0x38) = 1;
    *(int *)(*(int *)owner + 0x454) = 1;
    func_ov107_020c9264(*(int *)owner, 0xb, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov253_020ce19c);
}
