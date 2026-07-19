extern char *data_ov008_02090fac;
extern void func_0201e3cc(int value);


/* Fade-out step: same ramp as func_ov026_0208b188 but driving the brightness negative. */
int func_ov008_0208832c(void) {
    int *level = *(int **)&data_ov008_02090fac;
    int v = *level;
    if (v < 0x10) {
        v += 5;
        *level = v;
        if (v > 0x10) {
            *level = 0x10;
        }
        func_0201e3cc(-*level);
    } else {
        *level = 0;
        return 1;
    }
    return 0;
}
