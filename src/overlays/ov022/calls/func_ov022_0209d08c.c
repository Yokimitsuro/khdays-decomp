extern unsigned char data_0204c240;
void func_ov022_0209d08c(int arg0, int *arg1, short arg2) {
    *(short *)((char *)arg1 + 4) = 0;
    *arg1 = 0;
    if ((data_0204c240 & 2) != 0) *(short *)((char *)arg1 + 4) = arg2;
}
