extern int data_ov048_020b4b80;

void func_ov048_020b3a28(int this_) {
    int *base = (int *)(data_ov048_020b4b80 + 0x2c2c);
    base[0x45] = *(int *)(this_ + 0x263c) + 4;
    base[0xd5] = *(int *)(this_ + 0x2640) + 4;
}
