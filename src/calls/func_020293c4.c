extern void func_02029250();
extern void func_0202922c();

void func_020293c4(int this_, int arg1) {
    if ((*(unsigned char *)(arg1 + 0x20) & 1) == 0) return;
    func_02029250(this_, arg1);
    func_0202922c(this_, arg1);
    *(unsigned char *)(arg1 + 0x20) &= ~1;
}
