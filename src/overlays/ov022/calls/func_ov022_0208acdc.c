extern int func_01fffe14(void);
extern int func_ov022_02088474(unsigned int arg0);
extern void func_02033d0c(unsigned int arg0, unsigned int arg1, unsigned int *arg2, int arg3);

void func_ov022_0208acdc(int arg0, unsigned int *arg1, unsigned int arg2) {
    if (*(int *)(arg0 + 0xc) < 0) {
        return;
    }
    if (*(char *)(*(int *)(arg0 + *(int *)(arg0 + 0xc) * 4 + 0x18) + 0x110) !=
        func_ov022_02088474(func_01fffe14())) {
        return;
    }
    if (func_ov022_02088474(func_01fffe14()) == -1) {
        return;
    }
    func_02033d0c(*(unsigned int *)(arg0 + 0x10), arg2, arg1, 0);
}
