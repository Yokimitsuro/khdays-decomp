extern unsigned int func_ov022_02093a1c(int arg0);
extern void func_ov022_0209398c(int arg0, int arg1);
void func_ov022_02093f24(int arg0, int arg1) {
    if (arg1 < 2) return;
    if (arg1 >= 0xc) return;
    *(unsigned int *)(arg0 + 0x1c) |= 1 << func_ov022_02093a1c(arg1);
    func_ov022_0209398c(arg0, func_ov022_02093a1c(arg1));
}
