extern int func_0201ed3c(char *arg0, int arg1, unsigned int arg2, unsigned int arg3);
void func_ov022_020b11e8(unsigned char *arg0, char *arg1, int arg2, unsigned int arg3) {
    int r = func_0201ed3c(arg1, *(int *)(arg0 + 0x2c), *(unsigned short *)(arg0 + 0x32), arg3);
    *(int *)(arg0 + 0x28) = arg2;
    *(short *)(arg0 + 0x30) = r;
    *arg0 |= 1;
    arg0[3] = 1;
}
