extern unsigned char func_ov022_020882bc(int arg0);
extern unsigned short func_01fffe14(void);
extern void func_ov107_020c1f4c(int arg0, int arg1);
void func_ov022_020a0f2c(int arg0, int arg1) {
    unsigned int a = func_ov022_020882bc(*(unsigned char *)(arg0 + 9));
    unsigned short b = func_01fffe14();
    if (a != b) return;
    func_ov107_020c1f4c(arg1, *(int *)(arg0 + 0x4ec));
}
