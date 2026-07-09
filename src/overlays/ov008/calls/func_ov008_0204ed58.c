extern int *func_020315c0(int index);

unsigned int func_ov008_0204ed58(void)
{
    unsigned short count = 0;
    int i = 0;

    while (i < 4) {
        int *entry = func_020315c0(i);

        if (entry != 0 && *entry != 0) {
            count++;
        }
        i++;
    }

    return count;
}
