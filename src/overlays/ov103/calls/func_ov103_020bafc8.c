extern int data_ov103_020bc120;

void func_ov103_020bafc8(int this_) {
    int *base = (int *)(data_ov103_020bc120 + 0x2c2c);
    base[0x45] = *(int *)(this_ + 0x263c) + 4;
    base[0xd5] = *(int *)(this_ + 0x2640) + 4;
}
