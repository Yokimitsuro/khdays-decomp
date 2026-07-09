extern char *data_ov008_02090fa4;
void func_ov008_02081430(void)
{
    char *base = data_ov008_02090fa4;
    base += 0x9000;
    if (((unsigned int)*(int *)(base + 0x55c) << 29) >> 31) {
        *(int *)(base + 0x4f4) = 9;
    }
}
