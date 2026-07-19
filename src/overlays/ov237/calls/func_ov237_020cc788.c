extern void func_0202a440(void *p);
extern void func_0203c7e8(int handle);
extern void func_ov107_020c9eac(int handle);
extern void func_0203d194(void *p);
extern void func_ov107_020c68ec(void *self);

/* Actor teardown: both animation binders (clearing their back-pointers), the three models, the
 * effect handle, then the 19 entries of the attachment table before freeing it. */
void func_ov237_020cc788(char *self) {
    int i;
    func_0202a440(self + 0x388);
    *(int *)(self + 0x394) = 0;
    func_0202a440(self + 0x3b0);
    *(int *)(self + 0x3bc) = 0;
    func_0203c7e8(*(int *)(self + 0x384));
    func_0203c7e8(*(int *)(self + 0x3ac));
    func_0203c7e8(*(int *)(self + 0x3e4));
    func_ov107_020c9eac(*(int *)(self + 0x3d8));
    for (i = 0; i < 0x13; i++) {
        func_0203c7e8(*(int *)(*(char **)(self + 0x490) + i * sizeof(long long)));
    }
    func_0203d194(*(void **)(self + 0x490));
    func_ov107_020c68ec(self);
}
