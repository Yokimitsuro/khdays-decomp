extern void func_0202a634(int a, int b, int c, int d);
extern void func_ov092_020bb170(int p);
extern int data_ov092_020bc4e0;
extern int data_ov092_020bc468;

void func_ov092_020bae3c(void) {
    int d = data_ov092_020bc4e0;
    int base = d + 0x2d94;
    *(int *)(base + 0x14) = 0;
    func_0202a634(base + 0x18, (int)&data_ov092_020bc468, 1, *(unsigned char *)(d + 9) + 7);
    func_ov092_020bb170(d);
}
