extern void func_ov022_0209fb60(int a, int b, int c);
extern void func_ov022_0209fb98(int a, int b, int c);
extern void func_ov002_02051d6c(int a, int b, int c);
extern void func_ov002_02051eec(int a, int b, int c, int d, int e);
extern int *data_ov101_020bc0e0;
void func_ov101_020baa28(int param) {
    int obj = (int)data_ov101_020bc0e0;
    func_ov022_0209fb60(obj, 1, 2);
    func_ov022_0209fb98(obj, 1, 1);
    if (*(signed char *)(obj + 0xf0d) != 0)
        *(unsigned char *)(obj + 0xf0c) |= 1;
    func_ov002_02051d6c(param + 0xf0c, obj + 0x2c2c, param + 0x910);
    func_ov002_02051eec(param + 0xf0c, obj + 0x2c2c, *(int *)(param + 0x2bd0),
                        *(unsigned char *)(param + 9), 0x78);
}
