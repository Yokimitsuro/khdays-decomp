extern char *data_0204c234;
extern int func_02019fac(void *ptr, int arg);

int func_02033c64(int arg) {
    char *base = data_0204c234;
    int value = *(short *)(base + 0xb46f6);

    if (value < 0) {
        return value;
    }

    return func_02019fac(base + 0xb44c4, arg);
}
