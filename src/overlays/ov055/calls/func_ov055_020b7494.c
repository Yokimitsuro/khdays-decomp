extern void func_ov022_02091474();

void func_ov055_020b7494(int this_) {
    int *base = (int *)(this_ + 0x2000);
    int i, off;
    for (i = 0, off = 0; i < 3; i++, off += 0x30) {
        func_ov022_02091474(base[0x191] + off);
    }
}
