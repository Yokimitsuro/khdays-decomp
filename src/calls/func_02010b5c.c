void func_02010b5c(int *p)
{
    int *node = (int *)p[0x2c / 4];
    while (node != 0) {
        node[8 / 4] = p[0x1c / 4];
        node = (int *)node[0xc / 4];
    }
    p[0x28 / 4] = p[0x1c / 4];
}
