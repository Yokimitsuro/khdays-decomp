extern char *data_ov026_02091368;
extern void func_ov026_02086314(void);
extern void func_ov026_02085ddc(int a);
extern int func_ov026_02084d74(void *p, int a);
extern void func_ov026_02085bf4(void *dst, int src, int a, int b, int c, int d);
extern void func_ov026_0208a774(void);
extern void func_ov026_0208ac00(void);
extern void func_ov026_0208ac9c(void);

/* Enters the selection screen: builds the layout, blits the caption, marks every VRAM bank dirty
 * and picks the fade-in or the instant-show tick. */
void *func_ov026_0208ab5c(void) {
    int caption;
    void *next;
    func_ov026_02086314();
    func_ov026_02085ddc(5);
    caption = func_ov026_02084d74(*(char **)&data_ov026_02091368 + 0xc130, 6);
    func_ov026_02085bf4(*(char **)&data_ov026_02091368 + 0xc1d8, caption, 8, 8, 4, 8);
    *(int *)(*(char **)&data_ov026_02091368 + 0x2aac) |= 0x7f;
    func_ov026_0208a774();
    if (*(int *)(*(char **)&data_ov026_02091368 + 0xc3d8) == 0) {
        next = (void *)&func_ov026_0208ac00;
    } else {
        next = (void *)&func_ov026_0208ac9c;
    }
    return next;
}
