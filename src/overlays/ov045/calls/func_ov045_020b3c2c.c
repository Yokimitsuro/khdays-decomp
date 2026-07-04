extern int data_ov045_020b4c20;
extern void *func_ov022_020a35f4();

void *func_ov045_020b3c2c(int this_, int arg1) {
    char *base = (char *)(data_ov045_020b4c20 + 0x2df0);
    *(int *)(base + 0x114) = arg1;
    *(int *)(base + 0x118) = 0;
    return func_ov022_020a35f4(this_, 0x21, base, 0);
}
