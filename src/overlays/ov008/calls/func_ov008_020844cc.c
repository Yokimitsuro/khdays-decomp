extern char *data_ov008_02090fac;
extern void func_02032710(int handle, int cell, int visible);
extern long long func_02020400(int a, int b);
extern void func_ov008_020843f4(int y);

/* Resets the list to `total` entries: hides every row, recomputes the scrollbar thumb height
 * (clamped to 4..16 pixels) and shows the frame. */
void func_ov008_020844cc(int total) {
    char *st = *(char **)&data_ov008_02090fac;
    char *list = st + 0xc57c;
    int handle = *(int *)(st + 0xbfb0);
    int i;
    for (i = 0; i < 0xc; i++) {
        func_02032710(handle, *(int *)(list + i * sizeof(int) + 8), 0);
    }
    *(int *)(list + 0x3c) = total;
    *(int *)(list + 0x40) = 0;
    *(int *)(list + 0x48) = 0;
    if (total == 0) {
        *(int *)(list + 0x44) = 0x10;
    } else {
        *(int *)(list + 0x44) = (int)func_02020400(0x80, total);
        if (*(int *)(list + 0x44) < 4) {
            *(int *)(list + 0x44) = 4;
        }
        if (*(int *)(list + 0x44) > 0x10) {
            *(int *)(list + 0x44) = 0x10;
        }
    }
    *(int *)(list + 0x38) = *(int *)(list + 0x44) - 4;
    func_02032710(handle, *(int *)list, 1);
    func_02032710(handle, *(int *)(list + 4), 1);
    func_ov008_020843f4(0);
}
