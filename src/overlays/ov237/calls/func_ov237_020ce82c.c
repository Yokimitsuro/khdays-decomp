/* Fetch the target vector via 020cdb50 into +0x3c; unless busy mark state 2 and dispatch. */
extern void func_ov237_020cdb50(void *out, int self, int arg);
extern int func_0203c634(int, int, int);
struct w3 { int a, b, c; };
void func_ov237_020ce82c(int param_1) {
    int owner = *(int *)(param_1 + 4);
    struct w3 buf;
    func_ov237_020cdb50(&buf, param_1, *(int *)(*(int *)owner + 0x3d8) + 0x2c);
    *(struct w3 *)(owner + 0x3c) = buf;
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    *(signed char *)(*(int *)owner + 0x1c7) = 2;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
