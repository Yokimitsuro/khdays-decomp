extern int func_ov022_0209405c(unsigned char *arg0);
extern void func_0202aa9c(unsigned short *arg0);
void func_ov022_020942c4(unsigned char *arg0) {
    if (!func_ov022_0209405c(arg0)) return;
    if ((*arg0 & 0x20) == 0) return;
    func_0202aa9c((unsigned short *)(arg0 + 4));
}
