/* Clear +0x28, wipe the +0x4c scratch, kick anim 0xc, arm the 0x166/0x11 timer, clear the
 * +0x51 flag, then dispatch 020d000c. */
extern void MI_CpuFill8(void *, int, int);
extern int func_ov107_020c9264(int, int, int);
extern int func_ov107_020c5af8(int, int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov278_020d000c(int);
void func_ov278_020cffa4(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(int *)(owner + 0x28) = 0;
    MI_CpuFill8((void *)(owner + 0x4c), 0, 4);
    func_ov107_020c9264(*(int *)owner, 0xc, 0);
    func_ov107_020c5af8(*(int *)owner, 0x166, 0x11, *(int *)(owner + 0x38));
    *(unsigned char *)(owner + 0x51) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov278_020d000c);
}
