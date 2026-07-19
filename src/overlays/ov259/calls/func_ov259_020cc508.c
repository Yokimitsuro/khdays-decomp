extern void func_0202a440(void *p);
extern void func_0203c7e8(int handle);
extern void func_ov107_020c9eac(int handle);
extern void func_ov107_020c68ec(void *self);

/* Actor teardown: releases the resources this actor owns, then the shared base destructor. */

void func_ov259_020cc508(char *self) {
    int i;
    char *binder = self + 0x398;
    char *slot = self;
    for (i = 0; i < 2; i++) {
        func_0202a440(binder);
        *(int *)(slot + 0x3a4) = 0;
        binder += 0x24;
        slot += 0x24;
    }
    func_0202a440(self + 0x3e0);
    *(int *)(self + 0x3ec) = 0;
    func_0203c7e8(*(int *)(self + 0x38c));
    func_0203c7e8(*(int *)(self + 0x390));
    func_ov107_020c9eac(*(int *)(self + 0x414));
    for (i = 0; i < 0xd; i++) {
        func_0203c7e8(*(int *)(self + i * sizeof(long long) + 0x430));
    }
    func_ov107_020c68ec(self);
}
