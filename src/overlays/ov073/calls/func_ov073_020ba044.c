extern int func_01fff774(int, int, int);
extern int func_02016ae8(int, int, int);

void func_ov073_020ba044(int a, int *this) {
    int i;
    *(int *)((char *)this + 0x24) = 5;
    func_01fff774((int)this + 0x28, 0, 0);
    func_01fff774((int)this + 0x28, 2, 0);
    *(int *)((char *)this + 0xe0) = 0xccd;
    *(int *)((char *)this + 0xdc) = 0xccd;
    *(int *)((char *)this + 0xd8) = 0xccd;
    for (i = 0; i < 0xa; i++) {
        func_02016ae8(*(int *)((char *)this + 0xa0), i, 0);
    }
    func_02016ae8(*(int *)((char *)this + 0xa0), 7, 3);
}
