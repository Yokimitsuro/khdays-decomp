extern int func_01fffde0(int arg0);
extern void func_0202ba78(int arg0, unsigned int arg1, int arg2, int arg3);
extern void func_0202beb8(int arg0, int arg1);
extern int data_02041dc8;
void func_ov022_02088428(int arg0, int arg1) {
    int e = func_01fffde0(arg0);
    if (e == 0) return;
    func_0202ba78(*(char *)(e + 0x4bc), (unsigned short)arg1, 0, (int)&data_02041dc8);
    func_0202beb8(*(char *)(e + 0x4bc), 1);
    *(unsigned short *)(e + 0x66) = arg1;
}
