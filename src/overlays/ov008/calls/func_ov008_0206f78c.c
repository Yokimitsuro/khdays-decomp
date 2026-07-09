extern char *func_ov008_02050cec(void);
extern int data_ov008_02090f20;
int func_ov008_0206f78c(void)
{
    char *ptr = func_ov008_02050cec();
    if (data_ov008_02090f20 != 0) {
        return *(int *)(ptr + 8);
    }
    return 0;
}
