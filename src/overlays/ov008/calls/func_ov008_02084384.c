extern char *data_ov008_02090fac;
extern void func_02032710(int handle, int cell, int flag);

/* Hides the list frame and all twelve rows. */
void func_ov008_02084384(void) {
    char *st = *(char **)&data_ov008_02090fac;
    char *list = st + 0xc57c;
    int handle = *(int *)(st + 0xbfb0);
    int i;
    func_02032710(handle, *(int *)(st + 0xc57c), 0);
    func_02032710(handle, *(int *)(list + 4), 0);
    for (i = 0; i < 0xc; i++) {
        func_02032710(handle, *(int *)(list + i * sizeof(int) + 8), 0);
    }
}
