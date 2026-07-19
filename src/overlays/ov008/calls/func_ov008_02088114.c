extern char *data_ov008_02090fac;
extern void func_0201e374(int value);
extern void func_0201e3cc(int value);
extern void func_ov008_020878c4(void);

/* Fade-to-black step: 12 frames from full brightness to black, then reports -2 (done). */
int func_ov008_02088114(void) {
    int *level = *(int **)&data_ov008_02090fac;
    int result = 0;
    if (*level >= 0xc) {
        result -= 2;
    } else {
        int b = -(*level + 1) * 16 / 12;
        *level = *level + 1;
        func_0201e374(b);
        func_0201e3cc(b);
    }
    func_ov008_020878c4();
    return result;
}
