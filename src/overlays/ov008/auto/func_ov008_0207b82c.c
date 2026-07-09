extern char *data_ov008_02090f24;
int func_ov008_0207b82c(void)
{
    if (data_ov008_02090f24 != 0) {
        return *(unsigned short *)(data_ov008_02090f24 + 0x434);
    }
    return 0;
}
