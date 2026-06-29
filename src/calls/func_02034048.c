extern unsigned char *data_0204c234;
extern unsigned int func_0201cbe8(void *ptr);
extern unsigned int func_0201cc1c(void *ptr);

int func_02034048(int index) {
    unsigned int value = func_0201cbe8(data_0204c234 + 0xb44bc + index * 4) + 1;

    if (value >= func_0201cc1c(data_0204c234 + 0xb44bc + index * 4)) {
        value = -1;
    }

    return value;
}
