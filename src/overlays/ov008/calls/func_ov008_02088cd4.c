extern char *data_ov008_02090fac;
extern int func_ov008_02085dd4(void);
extern void func_ov008_02082f2c(int caption);
extern int func_ov008_02055c84(void *p, int id);
extern void func_ov008_02082fa8(int src, int arg);
extern void func_ov008_020878c4(void);
extern void func_ov008_02088d44(void);

/* Enters the detail view: picks the title-bar caption from the current tab and blits the entry's
 * description. */
void *func_ov008_02088cd4(void) {
    int caption;
    int entry = func_ov008_02085dd4();
    int tab = *(int *)(*(char **)&data_ov008_02090fac + 0xc250);
    switch (tab) {
    case 0:
        caption = 0xd;
        break;
    case 1:
        caption = 0x10;
        break;
    }
    func_ov008_02082f2c(caption);
    func_ov008_02082fa8(func_ov008_02055c84(*(char **)&data_ov008_02090fac + 0xc130, entry), -1);
    func_ov008_020878c4();
    return (void *)&func_ov008_02088d44;
}
