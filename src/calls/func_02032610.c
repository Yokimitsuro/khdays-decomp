extern int func_02011e58(void *p);

int func_02032610(char *arg0, int arg1) {
    if (arg1 < 0) {
        return 0;
    }
    return func_02011e58(arg0 + 0x18 + arg1 * 0x8c);
}
