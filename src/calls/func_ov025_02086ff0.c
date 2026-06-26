extern int func_01ff8830();
extern int func_01ff86fc();
extern int func_020100c8();
extern int *func_02010128();
extern int func_020236ac();

void func_ov025_02086ff0(char *r4) {
    int *r5;
    int *r6;

    func_01ff8830(r4 + 0x2c, 0, 0xa0);
    func_01ff86fc(0, r4 + 0xcc, 0x18);
    *(int *)(r4 + 0) = 0;
    *(int *)(r4 + 4) = 0;
    *(short *)(r4 + 0x70) = 1;

    r5 = func_02010128(r4 + 8, 0);
    if (r5 != 0) {
        do {
            r6 = func_02010128(r4 + 8, r5);
            func_020100c8(r4 + 8, r5);
            if (r5 != 0) {
                func_020236ac(r5);
            }
            r5 = r6;
        } while (r6 != 0);
    }

    r5 = func_02010128(r4 + 0x14, 0);
    if (r5 != 0) {
        do {
            r6 = func_02010128(r4 + 0x14, r5);
            func_020100c8(r4 + 0x14, r5);
            if (r5 != 0) {
                func_020236ac(r5);
            }
            r5 = r6;
        } while (r6 != 0);
    }

    r5 = func_02010128(r4 + 0x20, 0);
    if (r5 != 0) {
        do {
            r6 = func_02010128(r4 + 0x20, r5);
            func_020100c8(r4 + 0x20, r5);
            if (r5 != 0) {
                func_020236ac(r5);
            }
            r5 = r6;
        } while (r6 != 0);
    }
}
