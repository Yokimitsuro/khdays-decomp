extern void func_0202a440();
extern void func_0201f6b0();
extern void func_0201f5ac();
extern void func_0202a6d8();

void func_0202a7dc(int this_) {
    func_0202a440(this_ + 0xe0);
    if (*(int *)(this_ + 0x74) != 0) {
        func_0201f6b0(*(int *)(this_ + 0x74));
        func_0201f5ac(*(int *)(this_ + 0x74));
    }
    *(int *)(this_ + 0x74) = 0;
    func_0202a6d8(this_);
}
