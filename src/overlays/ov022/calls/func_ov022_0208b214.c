extern int func_01fffe14(void);
extern int func_ov022_02088474(int state);
extern short FX_Atan2(int a, int b);
extern void func_ov022_0208ffe8(int a);

struct Sel0208b214 { unsigned char sel : 3; };

void func_ov022_0208b214(int arg0) {
    unsigned char *pb = *(unsigned char **)(arg0 + 0x148);
    unsigned int mode = *(unsigned char *)(arg0 + 0x14c);
    int neg;
    if (mode == 0 || mode == 4) return;
    if (func_ov022_02088474(func_01fffe14()) !=
        ((struct Sel0208b214 *)(arg0 + 0x14d))->sel) return;
    neg = -1;
    if (func_ov022_02088474(func_01fffe14()) == neg) return;
    if (6 <= *pb && *pb <= 8) {
        if (*(unsigned char *)(arg0 + 0x14c) == 1) return;
    } else {
        *(short *)(arg0 + 0x98) = FX_Atan2(*(int *)(arg0 + 0x10), *(int *)(arg0 + 0x18));
        *(unsigned short *)(arg0 + 0x1c) |= 0x20;
    }
    func_ov022_0208ffe8(arg0 + 0x1c);
}
