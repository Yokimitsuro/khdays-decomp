extern void *func_02011aa0();
extern void func_020118ec();

int func_02011888(int this_, int *arg1) {
    void *r = func_02011aa0(this_, 0x4345424b);
    if (r == 0) {
        *arg1 = 0;
        return 0;
    }
    func_020118ec((char *)r + 8);
    *arg1 = (int)((char *)r + 8);
    return 1;
}
