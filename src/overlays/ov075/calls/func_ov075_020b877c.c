extern void func_0202a634(int a, int b, int c, int d);
extern void func_ov075_020b8ab0(int p);
extern int data_ov075_020b9e20;
extern int data_ov075_020b9da8;

void func_ov075_020b877c(void) {
    int d = data_ov075_020b9e20;
    int base = d + 0x2d94;
    *(int *)(base + 0x14) = 0;
    func_0202a634(base + 0x18, (int)&data_ov075_020b9da8, 1, *(unsigned char *)(d + 9) + 7);
    func_ov075_020b8ab0(d);
}
