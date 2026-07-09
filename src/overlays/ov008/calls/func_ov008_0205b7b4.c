extern int func_ov008_02050cd4(void);
int func_ov008_0205b7b4(void)
{
    int base = func_ov008_02050cd4();
    if (base != 0) {
        return *(int *)(base + 0x1408);
    }
    return -1;
}
