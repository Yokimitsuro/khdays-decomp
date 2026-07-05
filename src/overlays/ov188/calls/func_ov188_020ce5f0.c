extern void func_0203c5c0();
extern void func_ov188_020ceb78(void);

void func_ov188_020ce5f0(int this_) {
    int *result;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x40, func_ov188_020ceb78, 0, &result);
    *result = this_;
    result[1] = *(int *)(*result + 0x384);
    *(int **)(this_ + 0x214) = result;
}
