extern void *func_01fffd70(int x);
extern void *func_01fffd8c(int x);
extern void func_0203c8b0(int x);
void func_0203c148(int param_1) {
    void *e = func_01fffd70(param_1 + 0x88);
    if (e == 0) return;
    do {
        func_0203c8b0(*(int *)e);
        e = func_01fffd8c(param_1 + 0x88);
    } while (e != 0);
}
