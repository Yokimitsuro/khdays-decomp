extern void func_0202a634(int a, int b, int c, int d);
extern int data_ov036_020b4f04;

void func_ov036_020b497c(int this_) {
    char *a = (char *)(this_ + 0x2000);
    char *b = (char *)(this_ + 0x2c80);
    *(int *)(a + 0xc80) = 0;
    func_0202a634((int)(b + 0xc), (int)&data_ov036_020b4f04, 1, *(unsigned char *)(this_ + 9) + 7);
    *(int *)(b + 4) = 0;
    *(int *)(b + 8) = 0;
}
