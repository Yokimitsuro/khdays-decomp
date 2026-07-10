extern int func_01fffe14(void);
extern int func_ov022_02088474(int state);
extern int *func_020158e0(void);
extern void MI_Copy36B(int *dst, int *src);
extern void func_ov022_0208ffe8(int a);

struct Sel0208b2a8 { unsigned char sel : 3; };
struct Mtx0208b2a8 { int w[12]; };

void func_ov022_0208b2a8(int arg0) {
    unsigned char *pb = *(unsigned char **)(arg0 + 0x148);
    unsigned int mode = *(unsigned char *)(arg0 + 0x14c);
    int neg;
    struct Mtx0208b2a8 buf;
    if (mode == 0 || mode == 4) return;
    if (func_ov022_02088474(func_01fffe14()) !=
        ((struct Sel0208b2a8 *)(arg0 + 0x14d))->sel) return;
    neg = -1;
    if (func_ov022_02088474(func_01fffe14()) == neg) return;
    if (*pb >= 6 && *pb <= 8 && *(unsigned char *)(arg0 + 0x14c) == 1) return;
    buf = *(struct Mtx0208b2a8 *)func_020158e0();
    MI_Copy36B((int *)&buf, (int *)(arg0 + 0x9c));
    *(unsigned short *)(arg0 + 0x1c) &= ~0x20;
    func_ov022_0208ffe8(arg0 + 0x1c);
}
