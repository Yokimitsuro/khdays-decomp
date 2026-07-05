extern void func_0202a634(int a, int b, int c, int d);
extern void func_ov055_020b63d0(int p);
extern int data_ov055_020b7740;
extern int data_ov055_020b76c8;

void func_ov055_020b609c(void) {
    int d = data_ov055_020b7740;
    int base = d + 0x2d94;
    *(int *)(base + 0x14) = 0;
    func_0202a634(base + 0x18, (int)&data_ov055_020b76c8, 1, *(unsigned char *)(d + 9) + 7);
    func_ov055_020b63d0(d);
}
