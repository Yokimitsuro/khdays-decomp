extern int func_01fffde0(int arg0);
extern int func_0202aee0(unsigned short *arg0, int arg1);
int func_ov022_02088370(int arg0) {
    int e = func_01fffde0(arg0);
    if (e == 0) return 0;
    return func_0202aee0((unsigned short *)(*(int *)(e + 0x20) + 4), 0);
}
