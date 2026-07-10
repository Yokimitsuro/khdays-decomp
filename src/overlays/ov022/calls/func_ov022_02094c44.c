extern void func_0202a7dc(int arg0);
extern void func_ov022_02094c2c(unsigned int *arg0);

void func_ov022_02094c44(unsigned int *arg0, int arg1, int arg2, int arg3) {
    int i;
    unsigned int *p;
    if ((*arg0 & 1) != 0) {
        i = 0;
        p = arg0 + 3;
        do {
            func_0202a7dc((int)p);
            i = i + 1;
            p = p + 0x42;
        } while (i < 3);
        func_ov022_02094c2c(arg0);
    }
}
