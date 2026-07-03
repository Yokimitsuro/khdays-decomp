extern int data_ov034_020b5660;

void func_ov034_020b5124(int this) {
    int p = this + 0x22f8;
    int base = data_ov034_020b5660 + 0x2ce4;
    *(int *)(base + 0x10) = 0;
    *(int *)(base + 0x130) = *(int *)(p + 0x348) + 4;
    *(int *)(base + 0x134) = *(int *)(p + 0x344) + 4;
}
