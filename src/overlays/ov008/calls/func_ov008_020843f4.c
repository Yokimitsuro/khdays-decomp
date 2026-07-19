extern char *data_ov008_02090fac;
extern void func_0203257c(int handle, int cell, int *pos);
extern void func_02032710(int handle, int cell, int visible);

/* Repositions the whole list at scroll offset `y`: the frame, then every visible row 0.5 units
 * apart, then the scrollbar. Coordinates are 20.12 fixed point. */
void func_ov008_020843f4(int y) {
    char *st = *(char **)&data_ov008_02090fac;
    int tab = *(int *)(st + 0xc250);
    int *list = (int *)(st + 0xc57c);
    int handle = *(int *)(st + 0xbfb0);
    int pos[2];
    int i;
    pos[0] = tab == 3 ? 0xe0000 : 0xd0000;
    pos[1] = (y + 0x18) << 0xc;
    func_0203257c(handle, list[0], pos);
    pos[1] += 0x10000;
    for (i = 0; i < list[14]; i++) {
        func_02032710(handle, list[i + 2], 1);
        func_0203257c(handle, list[i + 2], pos);
        pos[1] += 0x8000;
    }
    func_0203257c(handle, list[1], pos);
}
