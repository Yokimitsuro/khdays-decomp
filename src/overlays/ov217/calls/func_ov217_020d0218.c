struct row8 { void *p, *q; };
extern void func_0202a440(void *p);
extern void func_0203c7e8(void *p);
extern void func_ov107_020c68ec(void *this);

void func_ov217_020d0218(char *this) {
    int i;
    func_0202a440(this + 0x388);
    *(int *)(this + 0x394) = 0;
    func_0203c7e8(*(void **)(this + 0x384));
    func_0203c7e8(*(void **)(this + 0x420));
    func_0203c7e8(*(void **)(this + 0x3c4));
    for (i = 0; i < 5; i++) {
        func_0203c7e8(((struct row8 *)this)[i + 0x88].p);
    }
    func_ov107_020c68ec(this);
}
