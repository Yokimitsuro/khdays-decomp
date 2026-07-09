extern char *data_ov008_02090fa4;
int func_ov008_020816c0(void)
{
    if (data_ov008_02090fa4 != 0) {
        return *(int *)(data_ov008_02090fa4 + 0x94f4);
    }
    return -1;
}
