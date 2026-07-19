extern char *data_ov026_02091368;
extern void func_0203011c(void *p, int a, int b, int c, int d);
extern void func_02032450(int handle, int cell);

/* Re-lays out the detail panel and refreshes its six cells. */
void func_ov026_0208a24c(void) {
    int handle;
    char *st = *(char **)&data_ov026_02091368;
    char *cells = st + 0xc4f4;
    handle = *(int *)(st + 0xbfb0);
    func_0203011c(st + 0xc160, 0x28, 0x38, 0xb0, 0x40);
    func_02032450(handle, *(int *)(st + 0xc5e0));
    func_02032450(handle, *(int *)(st + 0xc5e4));
    func_02032450(handle, *(int *)(st + 0xc5e8));
    func_02032450(handle, *(int *)(st + 0xc5ec));
    func_02032450(handle, *(int *)(cells + 0x50));
    func_02032450(handle, *(int *)(cells + 0x4c));
    *(int *)(st + 0xc320) = 0;
}
