extern int data_ov086_020b9a60;

void func_ov086_020b8908(int this_) {
    int *base = (int *)(data_ov086_020b9a60 + 0x2c2c);
    base[0x45] = *(int *)(this_ + 0x263c) + 4;
    base[0xd5] = *(int *)(this_ + 0x2640) + 4;
}
