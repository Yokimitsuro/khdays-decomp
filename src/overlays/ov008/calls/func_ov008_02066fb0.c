extern char *func_ov008_02050cd4(void);
extern void func_ov008_02062d00(void *context, int arg1, int arg2);

void func_ov008_02066fb0(void)
{
    char *context = func_ov008_02050cd4();

    if (*(int *)(context + 0x30) == 0 && *(int *)(context + 0x18) != 0) {
        func_ov008_02062d00(context, 0, 1);
    }
}
