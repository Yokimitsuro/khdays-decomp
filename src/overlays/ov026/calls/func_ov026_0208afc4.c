extern char *data_ov026_02091368;
extern void func_0201e374(int value);
extern void func_0201e3cc(int value);
extern void func_ov026_0208a774(void);

/* Fade-to-black step: 12 frames from full brightness to black, then reports -2 (done). */
int func_ov026_0208afc4(void) {
    int *level = *(int **)&data_ov026_02091368;
    int result = 0;
    if (*level >= 0xc) {
        result -= 2;
    } else {
        int b = -(*level + 1) * 16 / 12;
        *level = *level + 1;
        func_0201e374(b);
        func_0201e3cc(b);
    }
    func_ov026_0208a774();
    return result;
}
