extern char *data_0204c234;
extern int func_0201c608(void *ptr, int arg1, int arg2);

int func_02033b78(int arg0, int arg1) {
    if (arg0 == 0) {
        arg0 = *(int *)(data_0204c234 + 0x9c);
    }

    return func_0201c608(data_0204c234 + 0xb44c8, arg0, arg1);
}
