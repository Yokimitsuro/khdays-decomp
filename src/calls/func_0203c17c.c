extern void *func_01fffd70();
extern void func_0203c8e4();
extern void *func_01fffd8c();

void func_0203c17c(int this_) {
    void *r = func_01fffd70(this_ + 0x88);
    while (r != 0) {
        func_0203c8e4(*(int *)r);
        r = func_01fffd8c(this_ + 0x88);
    }
}
