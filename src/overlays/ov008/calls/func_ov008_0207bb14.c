extern char *data_ov008_02090f24;
extern int func_ov008_0207baf8(void);

int func_ov008_0207bb14(void)
{
    if (data_ov008_02090f24 == 0) {
        return 1;
    }

    if (func_ov008_0207baf8() != 0) {
        return 1;
    }

    return *(int *)(data_ov008_02090f24 + 0x4fc);
}
