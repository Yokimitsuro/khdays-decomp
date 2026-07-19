extern char *func_ov025_02084afc(void);
extern void func_ov025_0209d708(void);
extern void func_ov025_0209d720(void);
extern int func_ov025_02084a50(void);
extern int func_ov025_02084a7c(void);
extern void func_ov025_0209d89c(void);
extern void func_ov025_0209d974(void);
extern void func_ov025_0209da74(void);
extern void func_ov025_0209daf0(void);
extern void func_ov025_0209dd44(void);
extern void func_ov025_0209dc10(int page);
extern void func_ov025_0209e3f8(void);
extern void func_ov025_02084f78(int node, int a, int b);

/* Brings the list screen up: caches the two active objects, initialises every widget, selects
 * the current row and moves the state field to 1. */
int func_ov025_0209e41c(void) {
    char *self = func_ov025_02084afc();
    func_ov025_0209d708();
    func_ov025_0209d720();
    *(int *)(self + 0xc4) = func_ov025_02084a50();
    *(int *)(self + 0xc8) = func_ov025_02084a7c();
    func_ov025_0209d89c();
    func_ov025_0209d974();
    func_ov025_0209da74();
    func_ov025_0209daf0();
    func_ov025_0209dd44();
    func_ov025_0209dc10(*(short *)(self + 4));
    func_ov025_0209e3f8();
    func_ov025_02084f78(*(int *)(self + *(short *)(self + 2) * 8 + 0xd0), 0, 0);
    *(int *)(self + 0xc) = (*(int *)(self + 0xc) & ~0xf0) | 0x10;
    return 1;
}
