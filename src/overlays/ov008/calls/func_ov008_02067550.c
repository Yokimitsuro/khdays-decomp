extern char *func_ov008_02050cd4(void);
extern void func_ov008_020674e8(void *context, int arg1);
extern void func_ov008_0205cde8(void *context, int arg1);

void func_ov008_02067550(void)
{
    char *context = func_ov008_02050cd4();

    if (*(int *)(context + 0x30) == 0) {
        func_ov008_020674e8(context, 1);
        func_ov008_0205cde8(context, 1);
    }
}
