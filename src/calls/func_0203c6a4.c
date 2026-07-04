extern void *func_01fffd70();
extern void *func_01fffd8c();

void *func_0203c6a4(int this_, int arg1) {
    void *r = func_01fffd70(this_);
    while (r != 0) {
        if (*(int *)((char *)r + 4) == arg1) return r;
        r = func_01fffd8c(this_);
    }
    return 0;
}
