typedef int (*fp)();

int func_0203c8e4(char *p) {
    fp f = *(fp *)(p + 0x80);
    if (f == 0)
        return;
    return f();
}
