extern char *data_ov008_02090fb0;

int func_ov008_0208b838(int *out, int type, int index)
{
    if (type != 0x15) {
        return 0;
    }

    *out = *(int *)(*(char **)(data_ov008_02090fb0 + 0x14) + (index - 1) * 0x34 + 0xc);
    return 1;
}
