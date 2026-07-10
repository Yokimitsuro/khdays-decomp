extern int data_ov022_020b2e60;

void func_ov022_02083d54(unsigned char arg0) {
    int *g = &data_ov022_020b2e60;
    *(unsigned char *)(*g + 0x3e) = arg0;
    *(unsigned short *)*g |= 0x10;
    *(unsigned short *)*g |= 0x20;
}
