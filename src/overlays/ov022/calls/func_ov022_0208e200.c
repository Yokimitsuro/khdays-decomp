extern int func_01fffe14(void);
extern int func_ov022_02088474(int state);
extern void func_02016ae8(int a, int b, int c);
extern void func_ov022_0208ffe8(int a);

void func_ov022_0208e200(int arg0) {
    int e = *(int *)(arg0 + 0x44);
    int neg;
    if (*(signed char *)(e + 0x110) != func_ov022_02088474(func_01fffe14())) return;
    neg = -1;
    if (func_ov022_02088474(func_01fffe14()) == neg) return;
    func_02016ae8(*(int *)(e + 0x80), 2, 0);
    func_02016ae8(*(int *)(e + 0x80), 3, 0);
    if ((*(unsigned int *)(e + 0x158) & 1) != 0) {
        func_02016ae8(*(int *)(e + 0x80), 2, 3);
        func_02016ae8(*(int *)(e + 0x80), 3, 3);
    }
    func_ov022_0208ffe8(e + 8);
    func_02016ae8(*(int *)(e + 0x80), 2, 3);
    func_02016ae8(*(int *)(e + 0x80), 3, 3);
}
