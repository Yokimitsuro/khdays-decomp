/* Push the +0x28 vector into 020d43a4; unless busy mark state 5 and dispatch. */
extern int func_0203c634(int, int, void *);
struct w3 { int a, b, c; };
extern int func_ov199_020d43a4(int, struct w3, int);
void func_ov199_020d4edc(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov199_020d43a4(owner, *(struct w3 *)(owner + 0x28), 1);
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    *(signed char *)(*(int *)owner + 0x1c7) = 5;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
