extern char *data_ov026_02091368;
extern void func_0203011c(void *p, int a, int b, int c, int d);
extern int func_ov026_02084d74(void *p, int id);
extern void func_ov026_02085bf4(void *dst, int src, int x, int y, int w, int h);

/* Redraws the title bar with the given caption. */
void func_ov026_02085ddc(int caption) {
    char *bar = *(char **)&data_ov026_02091368 + 0xc19c;
    func_0203011c(bar, 0, 0, 0xb0, 0x10);
    func_ov026_02085bf4(bar,
                        func_ov026_02084d74(*(char **)&data_ov026_02091368 + 0xc130, caption),
                        0xa9, 2, 4, 0x20);
}
