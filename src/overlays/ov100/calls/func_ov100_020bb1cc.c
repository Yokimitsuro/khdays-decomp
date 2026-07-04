extern int data_ov100_020bc1c0;
extern void *func_ov022_020a35f4();

void *func_ov100_020bb1cc(int this_, int arg1) {
    char *base = (char *)(data_ov100_020bc1c0 + 0x2df0);
    *(int *)(base + 0x114) = arg1;
    *(int *)(base + 0x118) = 0;
    return func_ov022_020a35f4(this_, 0x21, base, 0);
}
