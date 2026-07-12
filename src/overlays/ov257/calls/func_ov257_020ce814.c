/* Kick anim 0xd and the +0x3d0 sub-anim 0xc, reset four fields, then dispatch. */
extern int func_ov107_020c9264(int, int, int);
extern int func_ov107_020c9ee8(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov257_020ce870(int);
void func_ov257_020ce814(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)owner, 0xd, 0);
    func_ov107_020c9ee8(*(int *)(*(int *)owner + 0x3d0), 0xc, 0);
    *(int *)(owner + 0x44) = 0;
    *(signed char *)(owner + 0x73) = 0;
    *(int *)(owner + 0x54) = 0;
    *(signed char *)(owner + 0x76) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov257_020ce870);
}
