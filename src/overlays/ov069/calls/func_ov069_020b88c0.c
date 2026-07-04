extern void func_02030788();
extern void *func_020315c0();
extern int data_ov069_020ba9b8;

int func_ov069_020b88c0(int this_) {
    int result = 0xa;
    void *r;
    func_02030788();
    r = func_020315c0();
    if (r != 0) {
        result = (&data_ov069_020ba9b8)[*(int *)((char *)r + 4)];
    }
    if (this_ != 0) {
        *(int *)this_ = *(int *)((char *)r + 4);
    }
    return result;
}
