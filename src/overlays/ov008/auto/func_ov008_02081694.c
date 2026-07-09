extern char *data_ov008_02090fa4;

int func_ov008_02081694(void)
{
    char *base = data_ov008_02090fa4;

    if (base == 0) {
        return 1;
    }

    base += 0x9000;
    return ((unsigned int)*(int *)(base + 0x55c) << 29) >> 31;
}
