extern int data_0204c678;

void func_02035a34(int arg0) {
    int i = 0;
    int p = (int)&data_0204c678 + arg0 * 0x104;
    do {
        *(unsigned short *)(p + 0xba) = 0;
        i++;
        p += 4;
    } while (i < 0x12);
}
