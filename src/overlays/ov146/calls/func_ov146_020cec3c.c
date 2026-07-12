/* Unless busy or neither ready bit is set, pick the state and dispatch. */
extern int func_0203c634(int, int, void *);
struct bit0 { unsigned char b : 1; };
void func_ov146_020cec3c(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    int obj = *(int *)owner;
    if ((((struct bit0 *)(obj + 0x17a))->b) == 0 && (((struct bit0 *)(obj + 0x17c))->b) == 0) return;
    *(signed char *)(obj + 0x1c7) = *(int *)(owner + 0x1c) != 0 ? 3 : 2;
    *(int *)(owner + 0x10) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
