extern int func_01fffe14(void);
extern int func_ov022_02088474(int state);
extern void func_02016ae8(int a, int b, int c);
extern void func_ov022_0208ffe8(int a);

struct Flags0208fd70 { unsigned char b0 : 1; unsigned char b1 : 1; };

void func_ov022_0208fd70(int arg0) {
    int e = *(int *)(arg0 + *(int *)(arg0 + 0xc) * 4 + 0x18);
    int neg;
    if (*(signed char *)(e + 0x110) != func_ov022_02088474(func_01fffe14())) return;
    neg = -1;
    if (func_ov022_02088474(func_01fffe14()) == neg) return;
    func_02016ae8(*(int *)(e + 0x80), 10, 0);
    if (((struct Flags0208fd70 *)(e + 0x134))->b1)
        func_02016ae8(*(int *)(e + 0x80), 10, 3);
    func_ov022_0208ffe8(e + 8);
    func_02016ae8(*(int *)(e + 0x80), 10, 3);
}
