/* Unless the hw60 gate bit is set, copy the +0x38c vector into +0x14 and dispatch. */
extern int func_0203c634(int, int, void *);
struct hw60 { unsigned short lo : 8; unsigned short hi : 8; };
struct w3 { int a, b, c; };
void func_ov253_020d407c(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if ((((struct hw60 *)(*(int *)owner + 0x60))->lo & 1) == 0) return;
    *(struct w3 *)(owner + 0x14) = *(struct w3 *)(*(int *)owner + 0x38c);
    *(signed char *)(*(int *)owner + 0x1c7) = 1;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
