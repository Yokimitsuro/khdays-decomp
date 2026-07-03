extern int data_ov073_020ba540;

void func_ov073_020ba004(int this) {
    int p = this + 0x22f8;
    int base = data_ov073_020ba540 + 0x2ce4;
    *(int *)(base + 0x10) = 0;
    *(int *)(base + 0x130) = *(int *)(p + 0x348) + 4;
    *(int *)(base + 0x134) = *(int *)(p + 0x344) + 4;
}
