extern void func_ov002_02072034(void);
extern char *data_ov002_0207fa10;
/* Set widget `idx`'s state byte, returning the previous value; optionally re-layout. */
int func_ov002_020726f4(int idx, int value, int relayout) {
    int table = *(int *)((int)data_ov002_0207fa10 + 4);
    char *p = *(char **)(table + idx * 4 + 4);
    int old = *p;
    *p = value;
    if (relayout != 0) {
        func_ov002_02072034();
    }
    return old;
}
