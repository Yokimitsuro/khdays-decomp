/* Unless busy, kick anim 0x19, clear +0x5c/+0x60, then dispatch via c634. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov227_020d29e4(int);
void func_ov227_020d2994(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    func_ov107_020c9264(*(int *)owner, 0x19, 0);
    *(int *)(owner + 0x5c) = 0;
    *(int *)(owner + 0x60) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov227_020d29e4);
}
