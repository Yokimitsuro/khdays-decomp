extern void func_02003c38(void);
extern void func_0200fa08(void);
extern int data_02046d50[];

void func_0200f9ac(int param_1, unsigned param_2) {
    if ((param_2 & 0x3f) == 0x11) {
        int result;
        int (*fn)(void);
        if (data_02046d50[3] != 0) return;
        result = 0;
        fn = (int (*)(void))data_02046d50[6];
        if (fn != 0) result = fn();
        if (result != 0) func_0200fa08();
        data_02046d50[3] = 1;
    } else {
        func_02003c38();
    }
}
