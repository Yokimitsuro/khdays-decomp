extern void *func_01fffd70();
extern void *func_01fffd8c();

void *func_0203c6e0(int this_, int arg1) {
    void *r;
    if (arg1 == 0) return 0;
    r = func_01fffd70(this_);
    while (r != 0) {
        if (*(int *)((char *)r + 0x1c) == arg1) return r;
        r = func_01fffd8c(this_);
    }
    return 0;
}
