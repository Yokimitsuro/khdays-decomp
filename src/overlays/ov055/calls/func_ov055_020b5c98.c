extern void func_ov022_0209fb60(int a, int b, int c);
extern void func_ov022_0209fb98(int a, int b, int c);
extern void func_ov002_02051d6c(int a, int b, int c);
extern void func_ov002_02051eec(int a, int b, int c, int d, int e);
extern int *data_ov055_020b7740;
void func_ov055_020b5c98(int param) {
    int obj = (int)data_ov055_020b7740;
    func_ov022_0209fb60(obj, 0, 3);
    func_ov022_0209fb98(obj, 0, 1);
    if (*(signed char *)(obj + 0xda9) != 0)
        *(unsigned char *)(obj + 0xda8) |= 1;
    func_ov002_02051d6c(obj + 0xda8, obj + 0x2c2c, param + 0x910);
    func_ov002_02051eec(param + 0xda8, obj + 0x2c2c, *(int *)(param + 0x2bd0),
                        *(unsigned char *)(param + 9), 0x78);
}
