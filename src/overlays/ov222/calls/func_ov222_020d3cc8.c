/* Advance the +0x5c charge; arm the 020c5af8 bursts at the 0xcc0 and 0xbb0 thresholds; then dispatch. */
extern int func_ov107_020c5af8(int, int, int, int);
extern int func_0203c634(int, int, int);
void func_ov222_020d3cc8(int param_1) {
    int a = *(int *)param_1;
    int owner = *(int *)(param_1 + 4);
    *(int *)(owner + 0x5c) += *(int *)(a + 0x2c);
    if (!(*(unsigned char *)(owner + 0x75) & 1) && *(int *)(owner + 0x5c) >= 0xcc0) {
        func_ov107_020c5af8(*(int *)owner, 0x12a, 0xe, *(int *)(owner + 8));
        *(unsigned char *)(owner + 0x75) |= 1;
    }
    if (!(*(unsigned char *)(owner + 0x75) & 2) && *(int *)(owner + 0x5c) >= 0xbb0) {
        func_ov107_020c5af8(*(int *)owner, 0x12a, 4, *(int *)(owner + 8));
        *(unsigned char *)(owner + 0x75) |= 2;
    }
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    *(signed char *)(*(int *)owner + 0x1c7) = 6;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
