extern int data_ov057_020b74a0;
extern void func_02033e48();

void func_ov057_020b6304(int this_, int arg1) {
    int *base = (int *)(data_ov057_020b74a0 + 0x2c2c);
    *(int *)arg1 = 0;
    if (base[0x154] != 0) {
        func_02033e48(base[0x154]);
        base[0x154] = 0;
    }
}
