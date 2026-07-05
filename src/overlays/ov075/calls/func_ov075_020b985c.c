extern void func_0202a634(int a, int b, int c, int d);
extern int data_ov075_020b9de4;

void func_ov075_020b985c(int this_) {
    char *a = (char *)(this_ + 0x2000);
    char *b = (char *)(this_ + 0x2c80);
    *(int *)(a + 0xc80) = 0;
    func_0202a634((int)(b + 0xc), (int)&data_ov075_020b9de4, 1, *(unsigned char *)(this_ + 9) + 7);
    *(int *)(b + 4) = 0;
    *(int *)(b + 8) = 0;
}
