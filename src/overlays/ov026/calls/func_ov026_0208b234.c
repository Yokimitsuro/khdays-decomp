extern char *data_ov026_02091368;
extern int func_ov026_0208b188(void);
extern void func_ov026_02085aa4(void);
extern void func_ov026_020885cc(void);
extern void func_ov026_0208894c(void);
extern void func_ov026_02089854(void);
extern void func_ov026_02086210(void);
extern void func_ov026_02086af4(void *entry, int arg);
extern void func_ov026_0208a774(void);
extern void func_ov026_0208b2c0(void);

/* Idle tick of the selection screen: runs the fade, polls touch, refreshes the arrows, and then
 * whatever the current tab needs redrawing. */
void *func_ov026_0208b234(void) {
    char *view;
    char *st = *(char **)&data_ov026_02091368;
    void *next;
    int tab;
    char **rows;
    view = st + 0xc3c4;
    if (func_ov026_0208b188() != 0) {
        next = (void *)&func_ov026_0208b2c0;
    } else {
        next = 0;
    }
    func_ov026_02085aa4();
    func_ov026_020885cc();
    func_ov026_0208894c();
    tab = *(int *)(st + 0xc250);
    if (tab == 2) {
        *(int *)(view + 0x100) = 1;
        func_ov026_02089854();
        func_ov026_02086210();
    } else if (tab != 3) {
        rows = *(char ***)(view + 0xc);
        func_ov026_02086af4(rows != 0 ? rows[*(int *)view] : 0, -1);
    }
    func_ov026_0208a774();
    return next;
}
