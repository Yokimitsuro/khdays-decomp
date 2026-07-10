extern short func_02030788(void);
extern int func_01fffde0(int arg0);
extern void func_ov002_0206bbb8(int arg0, int arg1, int arg2);
void func_ov022_02088984(int arg0, int arg1) {
    if (func_02030788() != 0) return;
    if (func_01fffde0(arg0) == 0) return;
    if (arg1 <= 0) return;
    func_ov002_0206bbb8(arg0, 5, (arg1 << 0xc) >> 0xc);
}
