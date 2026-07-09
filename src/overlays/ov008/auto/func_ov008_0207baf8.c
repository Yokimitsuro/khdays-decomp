extern char *data_ov008_02090f24;
int func_ov008_0207baf8(void)
{
    if (data_ov008_02090f24 != 0) {
        return *(int *)(data_ov008_02090f24 + 0x4e8);
    }
    return 1;
}
