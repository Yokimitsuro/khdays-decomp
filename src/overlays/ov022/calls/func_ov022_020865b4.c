extern int func_ov022_02083f5c(void);
extern int func_ov002_02076d24(int arg0);

int func_ov022_020865b4(void) {
    int e = *(int *)(func_ov022_02083f5c() + 0x20);
    int r = 0;
    int t;
    if (e == 0) {
        return 0;
    }
    switch (*(int *)(e + 8)) {
    case 1:
        r = **(int **)(e + 0x10) + 4;
        break;
    case 2:
        t = func_ov002_02076d24(*(int *)(e + 0x18));
        if (t != 0) r = t;
        break;
    case 3:
        r = *(int *)(e + 0x1c) + 0x8f8;
        break;
    }
    return r;
}
