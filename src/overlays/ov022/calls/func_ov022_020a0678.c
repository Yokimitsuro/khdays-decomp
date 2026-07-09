extern void func_ov022_0209ccb0(int arg0, int arg1);
void func_ov022_020a0678(int arg0, int arg1) {
    unsigned char v = arg1;
    unsigned char *b = (unsigned char *)(arg0 + 0x694);
    void (*f)(int, int);
    *b = (*b & ~1) | (v & 1);
    func_ov022_0209ccb0(arg0, arg1);
    f = *(void (**)(int, int))(arg0 + 0x670);
    if (f == 0) return;
    f(arg0, arg1);
}
