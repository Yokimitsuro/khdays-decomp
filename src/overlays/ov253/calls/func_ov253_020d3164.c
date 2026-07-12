/* Unless the gate byte is set, clear +0x39c, mark state 2 and dispatch. */
extern int func_0203c634(int, int, int);
void func_ov253_020d3164(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(owner + 0xc)) != 0) return;
    *(signed char *)(*(int *)owner + 0x39c) = 0;
    *(signed char *)(*(int *)owner + 0x1c7) = 2;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
