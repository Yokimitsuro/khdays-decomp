extern void func_0203c7e8(int handle);
extern void func_ov107_020c9eac(int handle);
extern void func_ov107_020c68ec(void *self);

/* Actor teardown: releases the resources this actor owns, then the shared base destructor. */
void func_ov218_020cc294(char *self) {
    int i;
    func_0203c7e8(*(int *)(self + 0x384));
    func_ov107_020c9eac(*(int *)(self + 0x3ac));
    for (i = 0; i < 2; i++) {
        func_0203c7e8(*(int *)(self + i * sizeof(long long) + 0x3dc));
    }
    func_ov107_020c68ec(self);
}
