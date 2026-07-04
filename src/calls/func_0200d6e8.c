extern int func_0200d674();
extern void func_0200dce0();
extern void func_0200dcf0();
extern char data_02046438[];

int func_0200d6e8(int arg0) {
    int r = func_0200d674(arg0, func_0200dce0, 0);
    *(int *)(data_02046438 + 0x2c) = r;
    if (r == 0) {
        func_0200dcf0();
    }
    return *(int *)(data_02046438 + 0x2c);
}
