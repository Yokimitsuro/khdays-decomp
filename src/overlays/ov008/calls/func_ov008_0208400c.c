extern char *data_ov008_02090fac;
extern char *data_0204be18;
extern int func_ov008_02055808(void *p, unsigned short id);
extern void func_ov008_0205589c(void *p, int cell);
extern void func_0203011c(void *p, int a, int b, int c, int d);
extern void func_ov008_02083970(int handle, unsigned short value, void *cells);

/* First-time setup of the counter panel: loads its background, lays it out and fills in the two
 * totals from the save header. */
void func_ov008_0208400c(void) {
    char *st = *(char **)&data_ov008_02090fac;
    char *panel = st + 0xc324;
    char *layout = st + 0xc1d8;
    int handle = *(int *)(st + 0xbfb4);
    if (*(int *)(st + 0xc324) == 0) {
        func_ov008_0205589c(st + 0x5c, func_ov008_02055808(st + 0x5c, 0x3f5));
        func_0203011c(layout, 0, 0, 0xb0, 0x30);
        *(int *)panel = 1;
    }
    func_ov008_02083970(handle,
        *(unsigned short *)(*(char **)&data_0204be18 + 0x196a), panel + 8);
    func_ov008_02083970(handle,
        *(unsigned short *)(*(char **)&data_0204be18 + 0x1968), panel + 0x14);
}
