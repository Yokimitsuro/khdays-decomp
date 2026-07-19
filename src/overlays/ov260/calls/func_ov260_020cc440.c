extern void func_0202a440(void *p);
extern void func_0203c7e8(int handle);
extern void func_ov107_020c9eac(int handle);
extern void func_ov107_020c68ec(void *self);

/* Actor teardown: the animation binder, the four models, the effect handle, then whichever of the
 * twelve attachment slots are actually occupied. */
void func_ov260_020cc440(char *self) {
    int i;
    func_0202a440(self + 0x394);
    func_0203c7e8(*(int *)(self + 0x384));
    func_0203c7e8(*(int *)(self + 0x390));
    func_0203c7e8(*(int *)(self + 0x388));
    func_0203c7e8(*(int *)(self + 0x38c));
    func_ov107_020c9eac(*(int *)(self + 0x428));
    for (i = 0; i < 0xc; i++) {
        int h = *(int *)(self + i * sizeof(long long) + 0x478);
        if (h != 0) {
            func_0203c7e8(h);
        }
    }
    func_ov107_020c68ec(self);
}
