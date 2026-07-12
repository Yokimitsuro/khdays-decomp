/* Bail via 020d132c if not ready; else advance the +0x5c charge, arm the burst past 0x1650, dispatch. */
extern int func_ov221_020d132c(int, int);
extern int func_ov107_020c5af8(int, int, int, int);
extern int func_0203c634(int, int, int);
void func_ov221_020d3ad8(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (func_ov221_020d132c(param_1, 0) < 0) {
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
        return;
    }
    int a = *(int *)param_1;
    *(int *)(owner + 0x5c) += *(int *)(a + 0x2c);
    if (!(*(unsigned char *)(owner + 0x75) & 2) && *(int *)(owner + 0x5c) >= 0x1650) {
        func_ov107_020c5af8(*(int *)owner, 0x12a, 0xd, *(int *)(owner + 8));
        *(unsigned char *)(owner + 0x75) |= 2;
    }
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    *(signed char *)(*(int *)owner + 0x1c7) = 4;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
