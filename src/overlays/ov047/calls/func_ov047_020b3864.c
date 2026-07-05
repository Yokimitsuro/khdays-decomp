extern void func_0202a634(int a, int b, int c, int d);
extern void func_ov047_020b3a3c(int p);
extern int data_ov047_020b4380;
extern int data_ov047_020b4340;

void func_ov047_020b3864(void) {
    int d = data_ov047_020b4380;
    char *a = (char *)(d + 0x2000);
    char *b = (char *)(d + 0x2c50);
    *(int *)(a + 0xc50) = 0;
    *(int *)(b + 0x10) = 0;
    func_0202a634((int)(b + 0x14), (int)&data_ov047_020b4340, 1, *(unsigned char *)(d + 9) + 7);
    func_ov047_020b3a3c(d);
}
