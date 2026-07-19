extern char *data_ov008_02090fac;
extern void func_0203011c(void *p, int a, int b, int c, int d);
extern int func_ov008_02055c84(void *p, int id);
extern void func_ov008_02082d44(void *dst, int src, int x, int y, int w, int h);

/* Redraws the title bar with the given caption. */
void func_ov008_02082f2c(int caption) {
    char *bar = *(char **)&data_ov008_02090fac + 0xc19c;
    func_0203011c(bar, 0, 0, 0xb0, 0x10);
    func_ov008_02082d44(bar,
                        func_ov008_02055c84(*(char **)&data_ov008_02090fac + 0xc130, caption),
                        0xa9, 2, 4, 0x20);
}
