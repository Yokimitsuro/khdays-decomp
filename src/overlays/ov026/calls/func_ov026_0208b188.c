extern char *data_ov026_02091368;
extern void func_0201e3cc(int value);


/* Fade-in step: ramps the fade level up by 5 per frame and drives the master brightness until it
 * reaches full, then reports done. */
int func_ov026_0208b188(void) {
    int *level = *(int **)&data_ov026_02091368;
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
