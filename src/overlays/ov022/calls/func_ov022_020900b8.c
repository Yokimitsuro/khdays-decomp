extern int func_01fffe14(void);
extern int func_ov022_02088474(int state);
extern int *func_020158e0(void);
extern void MI_Copy36B(int *dst, int *src);
extern void func_ov022_0208ffe8(int a);

struct Mtx020900b8 { int w[12]; };

void func_ov022_020900b8(int arg0) {
    int e = *(int *)(arg0 + *(int *)(arg0 + 0xc) * 4 + 0x18);
    int neg;
    struct Mtx020900b8 buf;
    if (*(signed char *)(e + 0x110) != func_ov022_02088474(func_01fffe14())) return;
    neg = -1;
    if (func_ov022_02088474(func_01fffe14()) == neg) return;
    buf = *(struct Mtx020900b8 *)func_020158e0();
    MI_Copy36B((int *)&buf, (int *)(e + 0x88));
    *(unsigned short *)(e + 8) &= ~0x20;
    func_ov022_0208ffe8(e + 8);
}
