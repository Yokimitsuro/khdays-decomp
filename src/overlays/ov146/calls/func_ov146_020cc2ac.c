extern void func_0202a440(void *p);
extern void func_0203c7e8(int handle);
extern void func_ov107_020c9eac(int handle);
extern void func_ov107_020c68ec(void *self);

/* Actor teardown: releases the resources this actor owns, then the shared base destructor. */
void func_ov146_020cc2ac(char *self) {
    int i;
    func_0202a440(self + 0x388);
    func_0203c7e8(*(int *)(self + 0x384));
    for (i = 0; i < 5; i++) {
        int h = *(int *)(self + i * sizeof(long long) + 0x3c4);
        if (h != 0) {
            func_0203c7e8(h);
        }
    }
    func_ov107_020c68ec(self);
}
