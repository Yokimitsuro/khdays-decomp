/* Clear the +4 field, set (child)+0x2c = *child + 0xb0 and tail-call the dispatcher. */
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov210_020d40ac(int);
void func_ov210_020d4078(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(int *)(child + 4) = 0;
    *(int *)(child + 0x2c) = *(int *)child + 0xb0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov210_020d40ac);
}
