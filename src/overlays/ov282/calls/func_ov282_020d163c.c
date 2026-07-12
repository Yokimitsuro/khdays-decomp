/* Accumulate the owner rate (+0x2c) into the timer at (child)+0x2c; once it reaches
 * 0x1800, dispatch to the handler. */
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov282_020d1670(int);
void func_ov282_020d163c(int param_1) {
    int child = *(int *)(param_1 + 4);
    int t = *(int *)(child + 0x2c) + *(int *)(*(int *)param_1 + 0x2c);
    *(int *)(child + 0x2c) = t;
    if (t < 0x1800) return;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov282_020d1670);
}
