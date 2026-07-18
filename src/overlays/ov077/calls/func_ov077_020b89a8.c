extern int data_ov077_020b9b80;
extern int func_ov022_020a4490();

void func_ov077_020b89a8(int a, int *ctx) {
    int *row = (int *)(*(int *)&data_ov077_020b9b80 + 0x2c + 0x2c00);
    ctx[0x43] = 0;
    ctx[0] = 1;
    row[0x154] = func_ov022_020a4490(a, 0xc8, 5);
}
