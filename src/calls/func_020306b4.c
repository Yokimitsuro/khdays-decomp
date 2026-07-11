extern int func_02030670(void);
extern int func_02001030(void);

int func_020306b4(void) {
    int r4 = 0;
    if (func_02030670() == 0) return r4;
    {
        int v = func_02001030();
        if ((v >= 0 && v <= 1) || (v >= 9 && v <= 0xa)) {
            r4 = 1;
        }
    }
    return r4;
}
