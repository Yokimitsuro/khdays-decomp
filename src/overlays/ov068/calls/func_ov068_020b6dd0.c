extern int data_ov068_020b7500;
extern void *func_ov022_020a35f4();

void *func_ov068_020b6dd0(int this_, int arg1) {
    char *base = (char *)(data_ov068_020b7500 + 0x2cfc);
    *(int *)(base + 0x118) = arg1;
    *(int *)(base + 0x11c) = 0;
    return func_ov022_020a35f4(this_, 0x22, base, 0);
}
