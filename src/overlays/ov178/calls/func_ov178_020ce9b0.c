extern void func_ov107_020cb100();
extern void func_ov107_020c7ca4();

void func_ov178_020ce9b0(int this_) {
    if (*(signed char *)(this_ + 0x1c6) != 1 && *(int *)(this_ + 0x38c) != 0) {
        func_ov107_020cb100(*(int *)(this_ + 0x38c));
        *(int *)(this_ + 0x38c) = 0;
    }
    func_ov107_020c7ca4(this_);
}
