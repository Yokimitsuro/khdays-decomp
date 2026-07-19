extern char *data_ov008_02090fac;
extern void func_ov008_02083464(void);
extern void func_ov008_02082f2c(int a);
extern int func_ov008_02055c84(void *p, int a);
extern void func_ov008_02082d44(void *dst, int src, int a, int b, int c, int d);
extern void func_ov008_020878c4(void);
extern void func_ov008_02087d50(void);
extern void func_ov008_02087dec(void);

/* Enters the selection screen: builds the layout, blits the caption, marks every VRAM bank dirty
 * and picks the fade-in or the instant-show tick. */
void *func_ov008_02087cac(void) {
    int caption;
    void *next;
    func_ov008_02083464();
    func_ov008_02082f2c(5);
    caption = func_ov008_02055c84(*(char **)&data_ov008_02090fac + 0xc130, 6);
    func_ov008_02082d44(*(char **)&data_ov008_02090fac + 0xc1d8, caption, 8, 8, 4, 8);
    *(int *)(*(char **)&data_ov008_02090fac + 0x2aac) |= 0x7f;
    func_ov008_020878c4();
    if (*(int *)(*(char **)&data_ov008_02090fac + 0xc3d8) == 0) {
        next = (void *)&func_ov008_02087d50;
    } else {
        next = (void *)&func_ov008_02087dec;
    }
    return next;
}
