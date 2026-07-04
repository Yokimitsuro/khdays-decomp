extern void func_0202a7dc();
extern void func_0203d194();
extern void func_0203c900();

void func_0203c2c4(int this_) {
    func_0202a7dc(*(int *)(this_ + 0x88));
    func_0203d194(*(int *)(this_ + 0x88));
    if (*(int *)(this_ + 0x90) != 0) {
        func_0203d194(*(int *)(this_ + 0x90));
    }
    *(int *)(this_ + 0x90) = 0;
    *(int *)(this_ + 0x8c) = 0;
    func_0203c900(this_);
}
