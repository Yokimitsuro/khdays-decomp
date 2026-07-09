extern unsigned char data_0204c240;
extern void func_0202a7dc(int arg0, unsigned char *arg1, int arg2, int arg3);
void func_ov022_0209d278(int arg0, int arg1, int arg2, int arg3) {
    if ((data_0204c240 & 4) == 0) return;
    func_0202a7dc(arg0 + 0x7d4, &data_0204c240, arg2, arg3);
    *(short *)(arg0 + 0x8dc) = 0;
    *(unsigned char *)(arg0 + 0x694) &= ~0x10;
}
