extern void func_ov022_0209fb60(int a, int b, int c);
extern void func_ov022_0209fb98(int a, int b, int c);
extern void func_ov056_020b6134(int a);
extern int *data_ov056_020b7620;
void func_ov056_020b5cc8(void) {
    int obj = (int)data_ov056_020b7620;
    func_ov022_0209fb60(obj, 0, 1);
    func_ov022_0209fb98(obj, 0, 1);
    if (*(signed char *)(obj + 0xda9) != 0)
        *(unsigned char *)(obj + 0xda8) |= 1;
    func_ov022_0209fb60(obj, 1, 2);
    func_ov022_0209fb98(obj, 1, 1);
    if (*(signed char *)(obj + 0xf0d) != 0)
        *(unsigned char *)(obj + 0xf0c) |= 1;
    func_ov056_020b6134(obj);
}
