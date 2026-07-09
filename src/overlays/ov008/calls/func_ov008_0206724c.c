extern char *func_ov008_02050cd4(void);
extern void func_ov008_02063790(void *context, int arg1);
extern void func_02033b78(int arg0, int arg1);

void func_ov008_0206724c(void)
{
    char *context = func_ov008_02050cd4();

    if (*(int *)(context + 0x30) == 0) {
        func_ov008_02063790(context, 1);
        func_02033b78(0, 1);
    }
}
