extern void *func_02011aa0();
extern void func_020116f0();

int func_020116a8(int this_, int *arg1) {
    void *r = func_02011aa0(this_, 0x41424e4b);
    if (r == 0) {
        *arg1 = 0;
        return 0;
    }
    func_020116f0((char *)r + 8);
    *arg1 = (int)((char *)r + 8);
    return 1;
}
