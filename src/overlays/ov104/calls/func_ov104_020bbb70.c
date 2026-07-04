extern int data_ov104_020bc2a0;
extern void *func_ov022_020a35f4();

void *func_ov104_020bbb70(int this_, int arg1) {
    char *base = (char *)(data_ov104_020bc2a0 + 0x2cfc);
    *(int *)(base + 0x118) = arg1;
    *(int *)(base + 0x11c) = 0;
    return func_ov022_020a35f4(this_, 0x22, base, 0);
}
