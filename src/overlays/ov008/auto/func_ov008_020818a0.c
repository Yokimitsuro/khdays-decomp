extern char *data_ov008_02090fa4[];

int func_ov008_020818a0(unsigned int value)
{
    char *data = data_ov008_02090fa4[0];

    if (data == 0) {
        return 0;
    }

    if (value != 0 && value <= 4) {
        *(int *)(data + 0x9508) = value;
        return 1;
    }

    return 0;
}
