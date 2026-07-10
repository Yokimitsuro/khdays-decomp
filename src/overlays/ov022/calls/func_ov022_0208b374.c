extern int func_01fffe14(void);
extern int func_ov022_02088474(int state);
extern void func_02016b60(int a, int b, int c);
extern void func_ov022_0208ffe8(int a);

struct Sel0208b374 { unsigned char sel : 3; };

void func_ov022_0208b374(int arg0, int arg1, int arg2) {
    unsigned char *pb = *(unsigned char **)(arg0 + 0x148);
    unsigned int mode = *(unsigned char *)(arg0 + 0x14c);
    int neg;
    if (mode == 0 || mode == 4) return;
    if (func_ov022_02088474(func_01fffe14()) !=
        ((struct Sel0208b374 *)(arg0 + 0x14d))->sel) return;
    neg = -1;
    if (func_ov022_02088474(func_01fffe14()) == neg) return;
    if (*pb >= 6 && *pb <= 8 && *(unsigned char *)(arg0 + 0x14c) == 1) return;
    func_02016b60(*(int *)(arg0 + 0x94), arg1, arg2);
    func_ov022_0208ffe8(arg0 + 0x1c);
}
