extern char *data_ov008_02090f00;
int func_ov008_0204ec18(void)
{
    if (data_ov008_02090f00 != 0) {
        return *(unsigned short *)(data_ov008_02090f00 + 0x2c);
    }
    return 0;
}
