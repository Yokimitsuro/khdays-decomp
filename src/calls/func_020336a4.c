extern unsigned char *func_02032cbc(int arg);
extern void func_02032be8(int arg0, int arg1, int arg2);

void func_020336a4(int arg) {
    unsigned char *ptr = func_02032cbc(0);

    if (ptr == 0 || ptr[0] != 3) {
        func_02032be8(3, 0, (unsigned short)arg);
        return;
    }

    *(unsigned short *)(ptr + 2) = arg;
}
