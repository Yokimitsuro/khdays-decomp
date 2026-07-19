extern char *data_ov008_02090fac;
extern int func_ov008_02082ecc(int handle, int kind, int a, int b, int c);

/* Creates the list frame cell, the scrollbar cell and the twelve row cells. */
void func_ov008_02084284(void) {
    char *st = *(char **)&data_ov008_02090fac;
    char *list = st + 0xc57c;
    int handle = *(int *)(st + 0xbfb0);
    int i;
    *(int *)(st + 0xc57c) = func_ov008_02082ecc(handle, 0xc, 0, 0, 0);
    *(int *)(list + 4) = func_ov008_02082ecc(handle, 0xe, 0, 0, 0);
    for (i = 0; i < 0xc; i++) {
        *(int *)(list + i * sizeof(int) + 8) = func_ov008_02082ecc(handle, 0xd, 0, 0, 0);
    }
}
