extern void func_0202a440(void *p);
extern void func_0203c7e8(int handle);
extern void func_ov107_020c9eac(int handle);
extern void func_ov107_020c68ec(void *self);

/* Tears the actor down: both animation binders, the model and the effect handle, then the nine
 * attachment slots, and finally the shared base destructor. */
void func_ov238_020d00b4(char *self) {
    int i;
    func_0202a440(self + 0x394);
    func_0202a440(self + 0x3b8);
    func_0203c7e8(*(int *)(self + 0x388));
    func_ov107_020c9eac(*(int *)(self + 0x3e0));
    for (i = 0; i < 9; i++) {
        func_0203c7e8(*(int *)(self + i * sizeof(long long) + 0x404));
    }
    func_ov107_020c68ec(self);
}
