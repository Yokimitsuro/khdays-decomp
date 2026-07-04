extern int data_ov083_020b9b00;
extern void *func_ov022_020a35f4();

void *func_ov083_020b8b0c(int this_, int arg1) {
    char *base = (char *)(data_ov083_020b9b00 + 0x2df0);
    *(int *)(base + 0x114) = arg1;
    *(int *)(base + 0x118) = 0;
    return func_ov022_020a35f4(this_, 0x21, base, 0);
}
