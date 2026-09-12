extern void func_ov297_020d4168(int this_);
extern void func_ov297_020d4240(int this_);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov297_020d5354(int this_);

void func_ov297_020d52c0(int this_) {
    int node = *(int *)(this_ + 4);

    func_ov297_020d4168(this_);
    func_ov297_020d4240(this_);

    if (*(int *)(node + 0x60) >= 4 && *(int *)(node + 0x80) == 0) {
        *(signed char *)(*(int *)node + 0x1c7) = 0xa;
        func_0203c634((void *)this_, *(signed char *)(this_ + 0x20), 0);
        return;
    }
    if (*(int *)(node + 0x7c) >= 4) {
        *(signed char *)(*(int *)node + 0x1c7) = 9;
        func_0203c634((void *)this_, *(signed char *)(this_ + 0x20), 0);
        return;
    }
    func_0203c634((void *)this_, *(signed char *)(this_ + 0x20), (void *)func_ov297_020d5354);
}
