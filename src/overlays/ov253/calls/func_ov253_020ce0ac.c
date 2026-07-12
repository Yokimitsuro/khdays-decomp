/* Unless the child gate byte is set, kick anim 4 and dispatch via c634. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov253_020ce0f0(int);
void func_ov253_020ce0ac(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(owner + 4)) != 0) return;
    func_ov107_020c9264(*(int *)owner, 4, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov253_020ce0f0);
}
