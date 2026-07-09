extern unsigned char *func_ov008_02069b60(int arg0);
extern char data_ov008_02090504[];

void *func_ov008_02069b94(int arg0, int index)
{
    unsigned char *table = func_ov008_02069b60(arg0);

    if (index >= table[2]) {
        return 0;
    }

    return data_ov008_02090504 + (table + index)[3] * 4;
}
