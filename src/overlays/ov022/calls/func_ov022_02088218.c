typedef struct { int a, b, c; } T3_02088218;
extern int func_01fffde0(int arg0);
extern void func_0202b450(unsigned int *arg0, unsigned int *arg1);
extern void func_ov022_020a8940(int *arg0);
void func_ov022_02088218(int arg0, unsigned int *arg1) {
    int *e = (int *)func_01fffde0(arg0);
    if (e == 0) return;
    func_0202b450((unsigned int *)e[8], arg1);
    *(T3_02088218 *)(e + 0x123) = *(T3_02088218 *)arg1;
    func_ov022_020a8940(e);
}
