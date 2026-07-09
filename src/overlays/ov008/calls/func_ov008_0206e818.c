extern char *func_ov008_02050cec(void);
extern void func_ov008_0206bca0(void *context, int arg1, int arg2);
extern void func_02033b78(int arg0, int arg1);

void func_ov008_0206e818(void)
{
    char *context = func_ov008_02050cec();

    if (*(int *)(context + 8) == 0) {
        func_ov008_0206bca0(context, 0, 0x64);
        func_02033b78(0, 2);
    }
}
