extern char *data_ov008_02090fac;
extern int func_ov008_020882d8(void);
extern void func_ov008_02082bf4(void);
extern void func_ov008_0208571c(void);
extern void func_ov008_02085a9c(void);
extern void func_ov008_020869a4(void);
extern void func_ov008_02083360(void);
extern void func_ov008_02083c44(void *entry, int arg);
extern void func_ov008_020878c4(void);
extern void func_ov008_02088410(void);

/* Idle tick of the selection screen: runs the fade, polls touch, refreshes the arrows, and then
 * whatever the current tab needs redrawing. */
void *func_ov008_02088384(void) {
    char *view;
    char *st = *(char **)&data_ov008_02090fac;
    void *next;
    int tab;
    char **rows;
    view = st + 0xc3c4;
    if (func_ov008_020882d8() != 0) {
        next = (void *)&func_ov008_02088410;
    } else {
        next = 0;
    }
    func_ov008_02082bf4();
    func_ov008_0208571c();
    func_ov008_02085a9c();
    tab = *(int *)(st + 0xc250);
    if (tab == 2) {
        *(int *)(view + 0x100) = 1;
        func_ov008_020869a4();
        func_ov008_02083360();
    } else if (tab != 3) {
        rows = *(char ***)(view + 0xc);
        func_ov008_02083c44(rows != 0 ? rows[*(int *)view] : 0, -1);
    }
    func_ov008_020878c4();
    return next;
}
