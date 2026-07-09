extern void *func_ov008_02050cec(void);
extern int data_ov008_02090f20[];

int func_ov008_0206f824(void)
{
    void *context = func_ov008_02050cec();
    int result = 0;

    if (data_ov008_02090f20[0] == 0) {
        return result;
    }

    if (*(int *)context != 0 || *(int *)((char *)context + 0x14) != 0) {
        result = 1;
    }

    return result;
}
