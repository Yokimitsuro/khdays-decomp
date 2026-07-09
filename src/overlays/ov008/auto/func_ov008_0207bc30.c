extern char *data_ov008_02090f24;
int func_ov008_0207bc30(void)
{
    if (*(int *)(data_ov008_02090f24 + 0x498) != 0) {
        return 1;
    }
    return ((unsigned int)*(unsigned char *)(data_ov008_02090f24 + 0x42c) << 30) >> 31;
}
