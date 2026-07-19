extern void func_0202a440(char *p);
extern void func_0203c7e8(int h);
extern void func_ov107_020c9eac(int h);
extern void func_ov107_020c68ec(char *self);

/* Releases everything the node owns: the two animation blocks (clearing their handles), the
 * seven fixed sprites, the actor pool and up to sixteen row sprites. */
void func_ov256_020cc53c(char *self) {
    int i;
    func_0202a440(self + 0x388);
    *(int *)(self + 0x394) = 0;
    func_0202a440(self + 0x3b0);
    *(int *)(self + 0x3bc) = 0;
    func_0203c7e8(*(int *)(self + 0x384));
    func_0203c7e8(*(int *)(self + 0x3ac));
    func_0203c7e8(*(int *)(self + 0x3d4));
    func_0203c7e8(*(int *)(self + 0x3e0));
    func_0203c7e8(*(int *)(self + 0x3ec));
    func_0203c7e8(*(int *)(self + 0x3f8));
    func_0203c7e8(*(int *)(self + 0x404));
    func_ov107_020c9eac(*(int *)(self + 0x450));
    for (i = 0; i < 0x10; i++) {
        int h = *(int *)(self + i * sizeof(long long) + 0x46c);
        if (h != 0) {
            func_0203c7e8(h);
        }
    }
    func_ov107_020c68ec(self);
}
