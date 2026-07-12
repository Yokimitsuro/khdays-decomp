/* Tear down the actor: destroy the work list (+0x394), clear +0x3a0, release the two
 * main handles (+0x384 render, +0x388 anim), free all 8 slot handles at +0x3b8, then
 * release the handle table and the actor itself. */
extern void func_0202a440(int a);
extern void func_0203c7e8(int a);
extern void func_ov107_020c9eac(int a);
extern void func_0203d194(int a);
extern void func_ov107_020c68ec(int a);
struct row8_020cc45c { int p; int q; };
void func_ov231_020cc45c(int param_1) {
    int i;
    func_0202a440(param_1 + 0x394);
    *(int *)(param_1 + 0x3a0) = 0;
    func_0203c7e8(*(int *)(param_1 + 0x384));
    func_ov107_020c9eac(*(int *)(param_1 + 0x388));
    for (i = 0; i < 8; i++) {
        func_0203c7e8(((struct row8_020cc45c *)*(int *)(param_1 + 0x3b8))[i].p);
    }
    func_0203d194(*(int *)(param_1 + 0x3b8));
    func_ov107_020c68ec(param_1);
}
