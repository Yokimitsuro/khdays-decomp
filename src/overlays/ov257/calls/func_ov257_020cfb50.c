/* Kick anim 0x13 and the +0x3d0 sub-anim 0x10, reset four fields, then dispatch. */
extern int func_ov107_020c9264(int, int, int);
extern int func_ov107_020c9ee8(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov257_020cfbac(int);
void func_ov257_020cfb50(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)owner, 0x13, 0);
    func_ov107_020c9ee8(*(int *)(*(int *)owner + 0x3d0), 0x10, 0);
    *(signed char *)(owner + 0x73) = 0;
    *(int *)(owner + 0x44) = 0;
    *(int *)(owner + 0x54) = 0;
    *(signed char *)(owner + 0x76) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov257_020cfbac);
}
