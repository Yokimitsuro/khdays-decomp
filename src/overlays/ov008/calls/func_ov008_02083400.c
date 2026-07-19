extern char *data_ov008_02090fac;
extern void func_02032450(int handle, int cell);

/* Rebuilds all 24 cells of both sprite rows from the cached OAM template. */
void func_ov008_02083400(void) {
    char *ui = *(char **)&data_ov008_02090fac;
    int (*rows)[8] = (int (*)[8])(ui + 0xc254);
    int handle = *(int *)(ui + 0xbfb4);
    int i;
    for (i = 0; i < 0x18; i++) {
        func_02032450(handle, rows[i >> 3][i & 7]);
        func_02032450(handle, rows[(i >> 3) + 3][i & 7]);
    }
}
