extern void func_02029250();

void func_0202b3b0(int this_) {
    if ((*(int *)this_ & 8) == 0) return;
    if ((*(int *)this_ & 0x10) == 0) {
        func_02029250(*(int *)(*(int *)(*(int *)(this_ + 0x10c) + 4)), this_ + 0x110);
    }
    *(int *)this_ &= ~8;
}
