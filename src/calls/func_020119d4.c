extern void *func_02011aa0();
extern void func_02011a10();

int func_020119d4(int this_, int *arg1) {
    void *r = func_02011aa0(this_, 0x43484152);
    if (r == 0) {
        *arg1 = 0;
        return 0;
    }
    func_02011a10((char *)r + 8);
    *arg1 = (int)((char *)r + 8);
    return 1;
}
