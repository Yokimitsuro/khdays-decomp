extern void func_0202a634(int a, int b, int c, int d);
extern void func_ov066_020b623c(int p);
extern int data_ov066_020b6b80;
extern int data_ov066_020b6b40;

void func_ov066_020b6064(void) {
    int d = data_ov066_020b6b80;
    char *a = (char *)(d + 0x2000);
    char *b = (char *)(d + 0x2c50);
    *(int *)(a + 0xc50) = 0;
    *(int *)(b + 0x10) = 0;
    func_0202a634((int)(b + 0x14), (int)&data_ov066_020b6b40, 1, *(unsigned char *)(d + 9) + 7);
    func_ov066_020b623c(d);
}
