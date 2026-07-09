extern void *func_ov008_02050cd4(void);
extern void func_ov008_02062d00(void *context, int arg1, int arg2);

void func_ov008_02066fe0(void)
{
    void *context = func_ov008_02050cd4();

    if (*(int *)((char *)context + 0x1e78) >= 2 && *(int *)((char *)context + 0x30) == 0 && *(int *)((char *)context + 0x18) != 1) {
        func_ov008_02062d00(context, 1, 1);
    }
}
