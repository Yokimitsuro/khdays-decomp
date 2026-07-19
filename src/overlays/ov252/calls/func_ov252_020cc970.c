extern void func_0202a440(void *p);
extern void func_0203d194(void *p);
extern void func_0203c7e8(int handle);
extern void func_ov107_020c9eac(int handle);
extern void func_ov107_020c68ec(void *self);

/* Actor teardown: releases the resources this actor owns, then the shared base destructor. */

void func_ov252_020cc970(char *self) {
    int i;
    char *binder = self + 0x3a0;
    char *slot = self;
    char *binder2;
    char *slot2;
    for (i = 0; i < 4; i++) {
        func_0202a440(binder);
        *(int *)(slot + 0x3ac) = 0;
        binder += 0x24;
        slot += 0x24;
    }
    func_0202a440(self + 0x430);
    *(int *)(self + 0x43c) = 0;
    binder2 = self + 0x454;
    slot2 = self;
    for (i = 0; i < 4; i++) {
        func_0202a440(binder2);
        *(int *)(slot2 + 0x460) = 0;
        binder2 += 0x24;
        slot2 += 0x24;
    }
    func_ov107_020c9eac(*(int *)(self + 0x574));
    func_0203c7e8(*(int *)(self + 0x384));
    func_0203c7e8(*(int *)(self + 0x388));
    for (i = 0; i < 4; i++) {
        func_0203c7e8(*(int *)(self + i * sizeof(int) + 0x38c));
    }
    for (i = 0; i < 0x31; i++) {
        func_0203c7e8(*(int *)(self + i * sizeof(long long) + 0x63c));
    }
    func_ov107_020c68ec(self);
}
