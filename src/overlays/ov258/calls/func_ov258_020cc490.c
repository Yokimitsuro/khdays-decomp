extern void func_0202a440(void *p);
extern void func_0203c7e8(int handle);
extern void func_ov107_020c9eac(int handle);
extern void func_ov107_020c68ec(void *self);

/* Actor teardown: releases the resources this actor owns, then the shared base destructor. */

void func_ov258_020cc490(char *self) {
    int i;
    func_0202a440(self + 0x388);
    *(int *)(self + 0x394) = 0;
    func_0202a440(self + 0x3b0);
    *(int *)(self + 0x3bc) = 0;
    func_0203c7e8(*(int *)(self + 0x384));
    func_0203c7e8(*(int *)(self + 0x3ac));
    for (i = 0; i < 0x2b; i++) {
        func_0203c7e8(*(int *)(self + i * sizeof(long long) + 0x464));
    }
    func_ov107_020c68ec(self);
}
