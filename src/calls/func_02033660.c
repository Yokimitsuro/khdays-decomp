extern unsigned char *func_02032cbc(int arg);
extern void func_02032be8(int arg0, int arg1, int arg2);

int func_02033660(int arg) {
    unsigned char *ptr = func_02032cbc(0);

    if (ptr == 0 || ptr[0] != 1) {
        func_02032be8(1, arg, 0);
    } else {
        ptr[1] = arg;
    }

    return 1;
}
