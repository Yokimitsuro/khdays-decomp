/* Kick anim 0xc, retract via 020cc830, reset fields, set +0x5c=0xc00, then dispatch. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov283_020cc830(int, int);
extern int func_ov283_020ce73c(int);
void func_ov283_020ce6e0(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)owner, 0xc, 0);
    func_ov283_020cc830(*(int *)owner, 2);
    *(int *)(owner + 0x68) = 0;
    *(int *)(owner + 0x6c) = 0;
    *(int *)(owner + 0x48) = 0;
    *(int *)(owner + 0x74) = 0;
    *(int *)(owner + 0x5c) = 0xc00;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov283_020ce73c);
}
