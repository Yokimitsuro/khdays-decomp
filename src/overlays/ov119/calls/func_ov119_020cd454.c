/* Mark sub-state 5 at (*child)+0x1c7 and dispatch (no handler). */
extern int func_0203c634(int a, int b, void *handler);
void func_ov119_020cd454(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(signed char *)(*(int *)child + 0x1c7) = 5;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
}
