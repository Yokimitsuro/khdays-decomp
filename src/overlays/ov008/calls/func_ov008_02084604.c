extern char *data_ov008_02090fac;
extern int func_ov008_02055808(void *p, unsigned short id);
extern void func_ov008_0205589c(void *p, int cell);

/* Reloads every icon of the current tab except the selected one, then the selected one last so it
 * ends up on top. */
void func_ov008_02084604(void) {
    char *st = *(char **)&data_ov008_02090fac;
    char *tab = st + 0xc3b8;
    int i;
    int count;
    switch (*(int *)(st + 0xc250)) {
    case 2:
        count = 6;
        break;
    case 3:
        count = 2;
        break;
    default:
        count = 8;
        break;
    }
    for (i = 0; i < count; i++) {
        if (i != *(int *)(tab + 8)) {
            func_ov008_0205589c(st + 0x10, func_ov008_02055808(st + 0x10,
                (unsigned short)(*(int *)(tab + 4) + i)));
        }
    }
    func_ov008_0205589c(st + 0x10, func_ov008_02055808(st + 0x10,
        (unsigned short)(*(int *)tab + *(int *)(tab + 8))));
}
