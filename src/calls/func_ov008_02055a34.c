extern int func_020100c8();
extern int *func_02010128();

void func_ov008_02055a34(int *r6) {
    int *r5;
    int *r4;

    r5 = func_02010128(r6, 0);
    if (r5 != 0) {
        do {
            r4 = func_02010128(r6, r5);
            r5[8] &= ~1;
            func_020100c8(r6, r5);
            r5 = r4;
        } while (r4 != 0);
    }
    r6[6] = 0;
}
