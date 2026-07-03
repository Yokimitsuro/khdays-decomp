extern int data_ov090_020bcc00;

void func_ov090_020bc6c4(int this) {
    int p = this + 0x22f8;
    int base = data_ov090_020bcc00 + 0x2ce4;
    *(int *)(base + 0x10) = 0;
    *(int *)(base + 0x130) = *(int *)(p + 0x348) + 4;
    *(int *)(base + 0x134) = *(int *)(p + 0x344) + 4;
}
