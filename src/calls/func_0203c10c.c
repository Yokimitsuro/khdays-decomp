extern void *func_01fffd70();
extern void func_0203c86c();
extern void *func_01fffd8c();

void func_0203c10c(int this_, int arg1) {
    void *r = func_01fffd70(this_ + 0x88);
    while (r != 0) {
        func_0203c86c(*(int *)r, arg1);
        r = func_01fffd8c(this_ + 0x88);
    }
}
