extern void func_ov022_0209fb60(int a, int b, int c);
extern void func_ov022_0209fb98(int a, int b, int c);
void func_ov042_020b348c(int obj) {
    func_ov022_0209fb60(obj, 0, 1);
    func_ov022_0209fb98(obj, 0, 1);
    if (*(signed char *)(obj + 0xda9) != 0)
        *(unsigned char *)(obj + 0xda8) |= 1;
}
