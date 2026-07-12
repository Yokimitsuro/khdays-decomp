/* Reset via 020cdfe8, seed +0xc with a 3-word template, then unless busy accumulate the fall
 * speed into +0x64 and on overflow latch sub-state 0xd and dispatch. */
extern int func_ov252_020cdfe8(int, int, int);
extern int func_0203c634(int, int, void *);
extern int data_02041dc8;
struct w3 { int a, b, c; };
void func_ov252_020d2c0c(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov252_020cdfe8(param_1, 0, 1);
    *(struct w3 *)(owner + 0xc) = *(struct w3 *)&data_02041dc8;
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    int sum = *(int *)(owner + 0x64) + *(int *)(*(int *)param_1 + 0x2c);
    *(int *)(owner + 0x64) = sum;
    if (sum < 0x1000) return;
    *(unsigned char *)(*(int *)owner + 0x1c7) = 0xd;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
