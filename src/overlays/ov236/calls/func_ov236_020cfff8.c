/* Reset +0x28, clear the +0x4c block, kick anim 0xc, arm the 020c5af8 timer, then dispatch. */
extern void MI_CpuFill8(void *dst, int val, int size);
extern int func_ov107_020c9264(int, int, int);
extern int func_ov107_020c5af8(int, int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov236_020d0060(int);
void func_ov236_020cfff8(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(int *)(owner + 0x28) = 0;
    MI_CpuFill8((void *)(owner + 0x4c), 0, 4);
    func_ov107_020c9264(*(int *)owner, 0xc, 0);
    func_ov107_020c5af8(*(int *)owner, 0x127, 0x11, *(int *)(owner + 0x38));
    *(signed char *)(owner + 0x51) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov236_020d0060);
}
