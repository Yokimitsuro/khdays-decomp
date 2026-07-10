extern unsigned short func_02030788(void);
extern unsigned short func_01fffe14(void);
extern int func_ov022_02088474(unsigned int arg0);
extern void func_ov022_020b2020(int arg0, unsigned int arg1, int arg2, int *arg3);

void func_ov022_020ad2e4(int arg0, int arg1) {
    if (*(unsigned char *)(arg0 + 8) != func_02030788()) return;
    if (func_ov022_02088474(func_01fffe14()) !=
        func_ov022_02088474(*(unsigned char *)(arg0 + 9))) return;
    func_ov022_020b2020(0, *(unsigned char *)(arg0 + 9), arg1, (int *)(arg0 + 0x48c));
}
