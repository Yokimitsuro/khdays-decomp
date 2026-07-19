extern void func_ov022_0209fb60(int a, int b, int c);
extern void func_ov022_0209fb98(int a, int b, int c);
extern void func_ov002_02051d6c(int a, int b, int c);
extern void func_ov002_02051eec(int a, int b, int c, int d, int e);
extern int data_ov078_020ba4e0;

void func_ov078_020b8360(int self) {
    int base = *(int *)&data_ov078_020ba4e0;
    func_ov022_0209fb60(base, 0, 3);
    func_ov022_0209fb98(base, 0, 1);
    if (*(signed char *)(base + 0xda9) != 0) {
        *(unsigned char *)(base + 0xda8) |= 1;
    }
    func_ov002_02051d6c(base + 0xda8, base + 0x2c2c, self + 0x910);
    func_ov002_02051eec(self + 0xda8, base + 0x2c2c, *(int *)(self + 0x2bd0),
                        *(unsigned char *)(self + 9), 0x78);
    func_ov022_0209fb60(base, 1, 4);
    func_ov022_0209fb98(base, 1, 1);
    if (*(signed char *)(base + 0xf0d) != 0) {
        *(unsigned char *)(base + 0xf0c) |= 1;
    }
    func_ov002_02051d6c(base + 0xf0c, base + 0x2c80, self + 0x910);
    func_ov002_02051eec(self + 0xf0c, base + 0x2c80, *(int *)(self + 0x2bd0),
                        *(unsigned char *)(self + 9), 0xbe);
}
