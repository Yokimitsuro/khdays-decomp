extern char *func_ov008_02050cec(void);
extern void func_ov008_02074a4c(void *context, int arg1);
extern void func_02033b78(int arg0, int arg1);

void func_ov008_020781b4(void)
{
    if (*(int *)(func_ov008_02050cec() + 0x180) == 0) {
        func_ov008_02074a4c(func_ov008_02050cec(), 1);
        func_02033b78(0, 0);
    }
}
