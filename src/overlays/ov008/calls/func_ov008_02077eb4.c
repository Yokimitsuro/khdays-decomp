extern void func_ov008_020778a4(void *object, int arg1);
extern void func_ov008_02077974(void *object);

void func_ov008_02077eb4(void *object)
{
    int value = *(int *)((char *)object + 0x158);

    if (value != 0) {
        func_ov008_020778a4(object, value);
    }

    if (*(int *)((char *)object + 8) != 0) {
        func_ov008_02077974(object);
    }
}
