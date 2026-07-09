extern short func_02030788(void);
extern int func_01fffde0(int arg0);
extern int func_ov022_020a08a8(int arg0, unsigned int *arg1);
int func_ov022_02088398(int arg0, unsigned int *arg1) {
    int e;
    if (func_02030788() != 0) return 0;
    e = func_01fffde0(arg0);
    if (e != 0) return func_ov022_020a08a8(e, arg1);
    return 0;
}
