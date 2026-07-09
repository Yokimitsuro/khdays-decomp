extern char *data_ov008_02090fa0;
extern int func_ov008_0207b0a0(void);

int func_ov008_0207be38(void)
{
    int result = 0;

    if (*(int *)(data_ov008_02090fa0 + 0x28) == 0) {
        if (func_ov008_0207b0a0() != 0) {
            return 1;
        }
    }

    return result;
}
