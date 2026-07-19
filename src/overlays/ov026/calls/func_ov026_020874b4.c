extern char *data_ov026_02091368;
extern int func_ov026_02083530(void *p, unsigned short id);
extern void func_ov026_020835c4(void *p, int cell);

/* Reloads every icon of the current tab except the selected one, then the selected one last so it
 * ends up on top. */
void func_ov026_020874b4(void) {
    char *st = *(char **)&data_ov026_02091368;
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
            func_ov026_020835c4(st + 0x10, func_ov026_02083530(st + 0x10,
                (unsigned short)(*(int *)(tab + 4) + i)));
        }
    }
    func_ov026_020835c4(st + 0x10, func_ov026_02083530(st + 0x10,
        (unsigned short)(*(int *)tab + *(int *)(tab + 8))));
}
