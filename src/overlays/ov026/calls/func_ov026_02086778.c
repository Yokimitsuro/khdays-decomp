extern char *data_ov026_02091368;
extern void func_02032710(int handle, int cell, int visible);
extern void func_020325ec(int handle, int cell, unsigned short digit);

/* Draws a three-digit counter right-aligned, hiding the leading zeros. */
void func_ov026_02086778(unsigned int value, int *cells) {
    int handle = *(int *)(*(char **)&data_ov026_02091368 + 0xbfb4);
    int i;
    for (i = 2; i >= 0; i--) {
        if (i != 2 && value == 0) {
            func_02032710(handle, cells[i], 0);
        } else {
            func_02032710(handle, cells[i], 1);
            func_020325ec(handle, cells[i], (unsigned short)(value % 10));
        }
        value = value / 10;
    }
}
