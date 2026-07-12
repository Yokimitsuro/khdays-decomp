/* Tear down the actor: destroy the render instance at +0x384, free the four sub-instances
 * at +0x398 (stride 8), then release the actor itself. */
extern void func_0203c7e8(int a);
extern void func_ov107_020c68ec(int a);
struct row8_020d393c { int p; int q; };
void func_ov209_020d575c(int param_1) {
    int i;
    func_0203c7e8(*(int *)(param_1 + 0x384));
    for (i = 0; i < 4; i++) {
        func_0203c7e8(((struct row8_020d393c *)param_1)[i + 0x73].p);
    }
    func_ov107_020c68ec(param_1);
}
