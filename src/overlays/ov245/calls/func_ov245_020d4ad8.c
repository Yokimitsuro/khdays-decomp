extern void func_0203c7e8(int handle);
extern void func_ov107_020c9eac(int handle);
extern void func_ov107_020c68ec(void *self);

/* Actor teardown: releases the resources this actor owns, then the shared base destructor. */
void func_ov245_020d4ad8(char *self) {
    int i;
    func_0203c7e8(*(int *)(self + 0x384));
    func_ov107_020c9eac(*(int *)(self + 0x39c));
    for (i = 0; i < 3; i++) {
        func_0203c7e8(*(int *)(self + i * sizeof(long long) + 0x3b4));
    }
    func_ov107_020c68ec(self);
}
