extern int func_ov008_0206eb64(int arg0, int arg1, int arg2);
extern void func_ov008_0206f384(void);

void func_ov008_02065990(void *object)
{
    if (func_ov008_0206eb64(0x14, 0, 0) != 0) {
        func_ov008_0206f384();
        *(int *)((char *)object + 4) = 0;
    }
}
