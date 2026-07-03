extern int data_ov053_020b7e60;

void func_ov053_020b7924(int this) {
    int p = this + 0x22f8;
    int base = data_ov053_020b7e60 + 0x2ce4;
    *(int *)(base + 0x10) = 0;
    *(int *)(base + 0x130) = *(int *)(p + 0x348) + 4;
    *(int *)(base + 0x134) = *(int *)(p + 0x344) + 4;
}
