extern void func_0202a440(void *p);
extern void func_0203c7e8(int handle);
extern void func_ov107_020c9eac(int handle);
extern void func_ov107_020c68ec(void *self);

/* Actor teardown: releases the resources this actor owns, then the shared base destructor. */

void func_ov245_020cc434(char *self) {
    int i;
    int h;
    func_0202a440(self + 0x390);
    func_ov107_020c9eac(*(int *)(self + 0x4c8));
    func_ov107_020c9eac(*(int *)(self + 0x4cc));
    func_0203c7e8(*(int *)(self + 0x384));
    for (i = 0; i < 2; i++) {
        func_0203c7e8(*(int *)(self + i * sizeof(int) + 0x388));
    }
    h = *(int *)(self + 0x4dc);
    if (h != 0) {
        func_0203c7e8(h);
    }
    func_ov107_020c68ec(self);
}
