/* Tear down the actor: destroy the work list (+0x388) and the list at +0x3d4, release the
 * render (+0x384) and anim (+0x3b8) handles, free all 8 slot handles at +0x3d0, then release
 * the handle table and the actor itself. */
extern void func_0202a440(int a);
extern void func_0203d194(int a);
extern void func_0203c7e8(int a);
extern void func_ov107_020c9eac(int a);
extern void func_ov107_020c68ec(int a);
struct row8_020cfee8 { int p; int q; };
void func_ov210_020cfee8(int param_1) {
    int i;
    func_0202a440(param_1 + 0x388);
    func_0203d194(*(int *)(param_1 + 0x3d4));
    func_0203c7e8(*(int *)(param_1 + 0x384));
    func_ov107_020c9eac(*(int *)(param_1 + 0x3b8));
    for (i = 0; i < 8; i++) {
        func_0203c7e8(((struct row8_020cfee8 *)*(int *)(param_1 + 0x3d0))[i].p);
    }
    func_0203d194(*(int *)(param_1 + 0x3d0));
    func_ov107_020c68ec(param_1);
}
