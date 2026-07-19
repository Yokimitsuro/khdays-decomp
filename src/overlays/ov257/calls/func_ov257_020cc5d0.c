extern void func_0202a440(void *p);
extern void func_0203d194(void *p);
extern void func_0203c7e8(int handle);
extern void func_ov107_020c9eac(int handle);
extern void func_ov107_020c68ec(void *self);

/* Actor teardown: releases the resources this actor owns, then the shared base destructor. */

void func_ov257_020cc5d0(char *self) {
    int i;
    func_0202a440(*(void **)(self + 0x388));
    func_0203d194(*(void **)(self + 0x388));
    func_0202a440(*(void **)(self + 0x390));
    func_0203d194(*(void **)(self + 0x390));
    func_ov107_020c9eac(*(int *)(self + 0x3d0));
    func_0203c7e8(*(int *)(self + 0x384));
    func_0203c7e8(*(int *)(self + 0x38c));
    for (i = 0; i < 4; i++) {
        func_0203c7e8(*(int *)(self + i * sizeof(int) + 0x394));
    }
    for (i = 0; i < 4; i++) {
        func_0203c7e8(*(int *)(self + i * sizeof(int) + 0x3a4));
    }
    for (i = 0; i < 0xc; i++) {
        func_0203c7e8(*(int *)(*(char **)(self + 0x400) + i * sizeof(long long)));
    }
    func_0203d194(*(void **)(self + 0x400));
    func_ov107_020c68ec(self);
}
