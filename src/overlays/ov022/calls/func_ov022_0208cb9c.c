extern int func_01fffe14(void);
extern int func_ov022_02088474(unsigned int arg0);
extern void func_ov022_020900b8(int arg0);

void func_ov022_0208cb9c(int arg0, int arg1, int arg2, int arg3) {
    int e = *(int *)(arg0 + *(int *)(arg0 + 0xc) * 4 + 0x18);
    unsigned char c;
    if (*(char *)(e + 0x110) != func_ov022_02088474(func_01fffe14())) return;
    if (func_ov022_02088474(func_01fffe14()) == -1) return;
    c = *(unsigned char *)(e + 0x118);
    if (c == 4 || c == 0) return;
    func_ov022_020900b8(arg0);
}
