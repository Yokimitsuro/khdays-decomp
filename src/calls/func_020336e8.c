extern unsigned char *data_0204c234;
extern unsigned char *func_02032cbc(int arg);
extern void func_02032be8(int arg0, int arg1, int arg2);

void func_020336e8(int kind, int arg1, int arg2) {
    unsigned char *ptr;

    if (*(short *)(data_0204c234 + 0xb46f6) == arg1) {
        return;
    }

    ptr = func_02032cbc(0);
    if (ptr == 0 || ptr[0] != kind) {
        func_02032be8(kind, arg1, (unsigned short)arg2);
        return;
    }

    ptr[1] = arg1;
    *(unsigned short *)(ptr + 2) = arg2;
}
