/* Snapshot the 64-bit tick from 020031d4 into the base block at +0x4ae4/+0x4ae8, set +0x4ad8=7
 * and clear +0x4ad0. */
extern long long func_020031d4(void);
extern int data_ov000_0205ac24;
void func_ov000_02052f78(void) {
    int base = data_ov000_0205ac24;
    long long t = func_020031d4();
    *(int *)(base + 0x4ae4) = (int)t;
    *(int *)(base + 0x4ae8) = (int)(t >> 32);
    *(int *)(base + 0x4ad8) = 7;
    *(int *)(data_ov000_0205ac24 + 0x4ad0) = 0;
}
