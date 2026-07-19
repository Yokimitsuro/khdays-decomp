extern char *data_ov008_02090fac;
extern char *data_0204be18;
extern int func_ov008_02082ecc(int handle, int kind, int a, int x, int y);
extern void func_02032710(int handle, int cell, int visible);
extern int func_ov008_02054788(void *p, int id);
extern void func_ov008_02054ba4(void *p, int cell, int on);

/* Builds the totals panel for the summary tab: copies the two counters out of the save header,
 * creates their two cells and shows them. */
void func_ov008_020876d4(void) {
    char *st = *(char **)&data_ov008_02090fac;
    char *panel = st + 0xc54c;
    int handle = *(int *)(st + 0xbfb0);
    char *sound = st + 0x2ab0;
    *(short *)(panel + 0x28) = *(unsigned short *)(*(char **)&data_0204be18 + 0x196a);
    *(short *)(panel + 0x2a) = *(unsigned short *)(*(char **)&data_0204be18 + 0x1968);
    *(int *)(st + 0xc54c) = func_ov008_02082ecc(handle, 0x13, 0, 0x24000, 0xa000);
    *(int *)(panel + 4) = func_ov008_02082ecc(handle, 0x14, 0, 0x4c000, 0xa000);
    func_02032710(handle, *(int *)(st + 0xc54c), 1);
    func_02032710(handle, *(int *)(panel + 4), 1);
    func_ov008_02054ba4(sound, func_ov008_02054788(sound, 1), 1);
}
