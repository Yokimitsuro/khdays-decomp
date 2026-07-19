extern char *data_ov008_02090fac;
extern void func_0201e3cc(int value);


/* Fade-in step: ramps the fade level up by 5 per frame and drives the master brightness until it
 * reaches full, then reports done. */
int func_ov008_020882d8(void) {
    int *level = *(int **)&data_ov008_02090fac;
    int v = *level;
    if (v < 0x10) {
        v += 5;
        *level = v;
        if (v > 0x10) {
            *level = 0x10;
        }
        func_0201e3cc(*level - 0x10);
        return 0;
    }
    *level = 0;
    return 1;
}
