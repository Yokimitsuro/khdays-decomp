extern short *func_020218a4(void);

int func_02021994(void) {
    short *ptr = func_020218a4();
    int value = 0;

    if (ptr[0] == 1) {
        return *(int *)(ptr + 2) << 12;
    }

    if (ptr[0] == 0x10) {
        value = *(int *)(ptr + 2);
    }

    return value;
}
