extern int data_0204c234;

void func_02032844(void) {
    int base = *(int *)&data_0204c234 + 0xb4718;
    *(short *)(base + 0x80) = 0;
    *(short *)(base + 0x82) = 0;
    *(char *)(base + 0x84) = 0;
}
