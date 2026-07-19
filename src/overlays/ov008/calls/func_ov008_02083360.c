extern char *data_ov008_02090fac;
extern char *data_0204be18;
extern void func_ov008_02083248(int cell, void *row, int selected);

/* Redraws both three-entry columns, highlighting whichever row each column has selected. */
void func_ov008_02083360(void) {
    char *panel = *(char **)&data_ov008_02090fac + 0xc254;
    int i;
    char *left = panel;
    char *right = panel + 0x60;
    for (i = 0; i < 3; i++) {
        func_ov008_02083248(*(int *)(*(char **)&data_0204be18 + 8) + *(int *)(panel + 0xc8),
                            left, *(int *)(panel + 0xc0) == i ? 1 : 0);
        func_ov008_02083248(*(int *)(*(char **)&data_0204be18 + 0xc) + *(int *)(panel + 0xcc),
                            right, *(int *)(panel + 0xc4) == i ? 1 : 0);
        left += 0x20;
        right += 0x20;
    }
}
