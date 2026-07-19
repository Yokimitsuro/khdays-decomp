extern char *data_ov026_02091368;
extern int func_ov026_02088c84(void);
extern void func_ov026_02085ddc(int caption);
extern int func_ov026_02084d74(void *p, int id);
extern void func_ov026_02085e58(int src, int arg);
extern void func_ov026_0208a774(void);
extern void func_ov026_0208bbf4(void);

/* Enters the detail view: picks the title-bar caption from the current tab and blits the entry's
 * description. */
void *func_ov026_0208bb84(void) {
    int caption;
    int entry = func_ov026_02088c84();
    int tab = *(int *)(*(char **)&data_ov026_02091368 + 0xc250);
    switch (tab) {
    case 0:
        caption = 0xd;
        break;
    case 1:
        caption = 0x10;
        break;
    }
    func_ov026_02085ddc(caption);
    func_ov026_02085e58(func_ov026_02084d74(*(char **)&data_ov026_02091368 + 0xc130, entry), -1);
    func_ov026_0208a774();
    return (void *)&func_ov026_0208bbf4;
}
