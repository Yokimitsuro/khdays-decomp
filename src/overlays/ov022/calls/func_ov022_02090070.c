extern unsigned short func_01fffe14(void);
extern int func_ov022_02088474(unsigned int arg0);
extern void func_ov022_0208ffe8(unsigned short *arg0, int arg1);
void func_ov022_02090070(int arg0, int arg1, int arg2, int arg3) {
    int t = *(int *)(arg0 + *(int *)(arg0 + 0xc) * 4 + 0x18);
    if (*(char *)(t + 0x110) != func_ov022_02088474(func_01fffe14())) return;
    if (func_ov022_02088474(func_01fffe14()) == -1) return;
    func_ov022_0208ffe8((unsigned short *)(t + 8), 0xffffffff);
}
