/* For each variable-stride record, forward its fields to func_ov025_020892e4. */
extern void func_ov025_020892e4(int self, int a, int b, int c, int d, int e, int f);
void func_ov025_02088be4(int param_1, int param_2) {
    unsigned int n = *(unsigned int *)param_2;
    unsigned int i;
    int p = param_2 + 4;
    for (i = 0; i < n; i++) {
        func_ov025_020892e4(param_1, *(unsigned short *)(p + 0xc), p + 0x10,
            *(unsigned short *)(p + 0xe), *(int *)(p + 4), *(int *)(p + 8), 0);
        p += *(int *)p;
    }
}
