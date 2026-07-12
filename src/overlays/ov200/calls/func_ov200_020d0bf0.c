/* Clear +0x34 and tail-call the dispatcher. */
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov200_020d0c14(int);
void func_ov200_020d0bf0(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(int *)(child + 0x34) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov200_020d0c14);
}
