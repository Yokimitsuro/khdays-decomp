extern void func_ov107_020c7ca4();

void func_ov239_020cc424(int this_) {
    if ((*(unsigned char *)(this_ + 0x1c4) & 0xa) &&
        *(signed char *)(this_ + 0x1c6) != 0 &&
        *(signed char *)(this_ + 0x1c6) != 1 &&
        *(signed char *)(this_ + 0x1c6) != 3 &&
        *(signed char *)(this_ + 0x1c6) != 7) {
        *(signed char *)(this_ + 0x1c7) = 7;
    }
    func_ov107_020c7ca4(this_);
}
