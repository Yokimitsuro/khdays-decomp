extern int func_01fffde0(int arg0);
extern int func_ov022_020b1b88(int arg0);
extern int func_ov022_020b19ec(int *arg0, int arg1);
int func_ov022_02088cac(int arg0) {
    int e = func_01fffde0(arg0);
    int b;
    if (e == 0) return e;
    b = func_ov022_020b1b88(e + 0xd90);
    if (b == 0) return b;
    return func_ov022_020b19ec((int *)(e + 0xd90), 0x1a);
}
