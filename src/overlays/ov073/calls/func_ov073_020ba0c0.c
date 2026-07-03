extern int func_01fff774(int, int, int);
extern int func_02016ae8(int, int, int);

void func_ov073_020ba0c0(int a, int *this) {
    int i;
    *(int *)((char *)this + 0x24) = 1;
    func_01fff774((int)this + 0x28, 0, 0);
    func_01fff774((int)this + 0x28, 2, 0);
    *(int *)((char *)this + 0xe0) = 0x1000;
    *(int *)((char *)this + 0xdc) = 0x1000;
    *(int *)((char *)this + 0xd8) = 0x1000;
    for (i = 0; i < 7; i++) {
        func_02016ae8(*(int *)((char *)this + 0xa0), i, 0);
    }
    func_02016ae8(*(int *)((char *)this + 0xa0), 7, 3);
    func_02016ae8(*(int *)((char *)this + 0xa0), 8, 3);
    func_02016ae8(*(int *)((char *)this + 0xa0), 9, 3);
}
