/* When bit 0 of *(obj)+0x17a is clear, bail if the busy byte at *(child+0xc) is set. Then mark
 * sub-state 9 or 2 depending on whether +0x68 is set and dispatch with no handler. */
struct bit0 { unsigned char b : 1; };
extern int func_0203c634(int a, int b, void *handler);
void func_ov282_020d10f4(int param_1) {
    int child = *(int *)(param_1 + 4);
    int obj = *(int *)child;
    if (((struct bit0 *)(obj + 0x17a))->b == 0) {
        if (*(unsigned char *)*(int *)(child + 0xc) != 0) return;
    }
    if (*(int *)(child + 0x68) != 0) {
        *(signed char *)(obj + 0x1c7) = 9;
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
    } else {
        *(signed char *)(obj + 0x1c7) = 2;
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
    }
}
