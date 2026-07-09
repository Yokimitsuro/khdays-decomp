extern char *data_ov008_02090f04[];
extern int func_ov008_0204fc74(void);

void func_ov008_02050b3c(void)
{
    int index = func_ov008_0204fc74();

    if (index != -1) {
        *(unsigned char *)(data_ov008_02090f04[1] + 0x963c) |= 1 << index;
    }
}
