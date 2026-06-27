extern int data_0204bbfc[];

int *func_0201e4c8(void)
{
    int *p = (int *)data_0204bbfc[0x18 / 4];

    if (p != 0) {
        data_0204bbfc[0x18 / 4] = p[0];
        p[0] = 0;
    }
    return p;
}
