extern void func_ov008_02063790(void *context, int arg1);
extern void func_02033b78(int arg0, int arg1);

void func_ov008_020674e8(void *context, int value)
{
    *(int *)((char *)context + 0x20) = value;

    if (*(int *)((char *)context + 0xa4) == 1) {
        func_ov008_02063790(context, 2);
    } else {
        func_ov008_02063790(context, 5);
    }

    func_02033b78(0, 1);
}
