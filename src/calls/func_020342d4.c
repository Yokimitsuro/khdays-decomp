extern int data_0204c238;

int func_020342d4(int index) {
    int base = *(int *)&data_0204c238;
    return *(unsigned short *)(base + index * 0x14 + 0xc);
}
