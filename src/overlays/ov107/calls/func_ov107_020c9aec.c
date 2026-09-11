extern int func_01fffd70(int list);
extern int func_01fffd8c(int list);
extern int func_01fffd0c(int list, int handle);
extern char *data_ov107_020cbf1c;

void func_ov107_020c9aec(int obj) {
    char *self = data_ov107_020cbf1c;
    int list = (int)(self + 4);
    int handle = func_01fffd70(list);
    if (handle == 0) return;
    for (;;) {
        if (*(int *)handle == obj) {
            func_01fffd0c(list, handle);
            return;
        }
        handle = func_01fffd8c(list);
        if (handle == 0) return;
    }
}
