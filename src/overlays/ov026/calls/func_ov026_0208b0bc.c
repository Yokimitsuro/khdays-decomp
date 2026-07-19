extern char *data_ov026_02091368;
extern void func_ov026_02087f70(int arg);
extern void func_ov026_02086910(void);
extern void func_ov026_02085ddc(int caption);
extern void func_ov026_02089780(void);
extern void func_ov026_0208a584(void);
extern void func_ov026_0208a774(void);
extern void func_ov026_0208b234(void);
extern void func_ov026_0208b2c0(void);

/* Rebuilds the list for the current tab and picks the next state: the idle tick if the list is
 * live, otherwise straight back out. */
void *func_ov026_0208b0bc(void) {
    char *st = *(char **)&data_ov026_02091368;
    int caption;
    int tab;
    func_ov026_02087f70(*(int *)(st + 0xc3d4));
    func_ov026_02086910();
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
    func_ov026_02085ddc(caption);
    tab = *(int *)(st + 0xc250);
    if (tab == 2 && *(int *)(st + 0xc3d4) != 0) {
        func_ov026_02089780();
    } else if (tab == 3) {
        func_ov026_0208a584();
    }
    func_ov026_0208a774();
    *(int *)st = 0;
    if (*(int *)(st + 0xc3d4) != 0 && *(int *)(st + 0xc56c) != 0) {
        return (void *)&func_ov026_0208b234;
    }
    return (void *)&func_ov026_0208b2c0;
}
