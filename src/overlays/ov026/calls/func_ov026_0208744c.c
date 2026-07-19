extern char *data_ov026_02091368;
extern long long func_02020400(int a, int b);
extern void func_ov026_020872a4(int y);

/* Scrolls the list to the given row, clamped to the scrollable range. */
void func_ov026_0208744c(int row, int base) {
    char *list = *(char **)&data_ov026_02091368 + 0xc57c;
    int last;
    if (*(int *)(list + 0x3c) > 8) {
        *(int *)(list + 0x40) = row;
        if (row < 0) {
            row = 0;
        }
        last = *(int *)(list + 0x3c) - 8;
        if (row > last) {
            row = last;
        }
        func_ov026_020872a4(base + (int)func_02020400(
            row * ((0x10 - *(int *)(list + 0x44)) * 8), last));
    }
}
