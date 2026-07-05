extern void func_0202a634(int a, int b, int c, int d);
extern void func_ov036_020b3bd0(int p);
extern int data_ov036_020b4f40;
extern int data_ov036_020b4ec8;

void func_ov036_020b389c(void) {
    int d = data_ov036_020b4f40;
    int base = d + 0x2d94;
    *(int *)(base + 0x14) = 0;
    func_0202a634(base + 0x18, (int)&data_ov036_020b4ec8, 1, *(unsigned char *)(d + 9) + 7);
    func_ov036_020b3bd0(d);
}
