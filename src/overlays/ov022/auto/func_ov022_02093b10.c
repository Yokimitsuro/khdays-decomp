void func_ov022_02093b10(unsigned char *arg0, int arg1) {
    *arg0 = 0;
    arg0[1] = 0;
    *(int *)(arg0 + 0x1c) = 0;
    *(int *)(arg0 + 0x4d8) = arg1;
    *(int *)(arg0 + 0x4d4) = arg1 + 0xd90;
}
