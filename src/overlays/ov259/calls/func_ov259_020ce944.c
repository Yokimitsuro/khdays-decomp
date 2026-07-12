/* Advance the +0x68 timer; unless the child is busy, mark state 2 and dispatch. */
extern int func_0203c634(int, int, void *);
void func_ov259_020ce944(int param_1) {
    int a = *(int *)param_1;
    int owner = *(int *)(param_1 + 4);
    *(int *)(owner + 0x68) = *(int *)(owner + 0x68) + *(int *)(a + 0x2c);
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    *(signed char *)(*(int *)owner + 0x1c7) = 2;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
