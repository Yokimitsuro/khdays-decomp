extern int data_ov002_0207fa14;

void func_ov002_02072db0(int arg0) {
    int p = *(int *)&data_ov002_0207fa14;
    *(unsigned char *)(p + 0x54) |= 1 << arg0;
}
