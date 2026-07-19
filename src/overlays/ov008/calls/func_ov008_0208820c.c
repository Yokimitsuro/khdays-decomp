extern char *data_ov008_02090fac;
extern void func_ov008_020850c0(int arg);
extern void func_ov008_02083a60(void);
extern void func_ov008_02082f2c(int caption);
extern void func_ov008_020868d0(void);
extern void func_ov008_020876d4(void);
extern void func_ov008_020878c4(void);
extern void func_ov008_02088384(void);
extern void func_ov008_02088410(void);

/* Rebuilds the list for the current tab and picks the next state: the idle tick if the list is
 * live, otherwise straight back out. */
void *func_ov008_0208820c(void) {
    char *st = *(char **)&data_ov008_02090fac;
    int caption;
    int tab;
    func_ov008_020850c0(*(int *)(st + 0xc3d4));
    func_ov008_02083a60();
    switch (*(int *)(st + 0xc250)) {
    case 0:
        caption = 0xc;
        break;
    case 1:
        caption = 0xf;
        break;
    case 2:
        caption = 0x12;
        break;
    case 3:
        caption = 0x18;
        break;
    }
    func_ov008_02082f2c(caption);
    tab = *(int *)(st + 0xc250);
    if (tab == 2 && *(int *)(st + 0xc3d4) != 0) {
        func_ov008_020868d0();
    } else if (tab == 3) {
        func_ov008_020876d4();
    }
    func_ov008_020878c4();
    *(int *)st = 0;
    if (*(int *)(st + 0xc3d4) != 0 && *(int *)(st + 0xc56c) != 0) {
        return (void *)&func_ov008_02088384;
    }
    return (void *)&func_ov008_02088410;
}
