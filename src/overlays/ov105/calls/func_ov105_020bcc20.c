extern int func_ov105_020bcc4c(int a0, int a1, int a2);
extern int data_ov105_020bfa20;

int func_ov105_020bcc20(int a0, int a1) {
    int result = func_ov105_020bcc4c(a0, a1, 0xf00);
    if (result != 0) {
        return result;
    }
    *(unsigned short *)(*(char **)((char *)&data_ov105_020bfa20 + 4) + 0x16) = 0;
    return result;
}
