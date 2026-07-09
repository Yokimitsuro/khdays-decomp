extern char *func_ov008_02050cd4(void);
extern void func_ov008_0206f7b0(int arg0);
extern void func_ov008_0206eb64(int arg0, int arg1, int arg2);
extern void func_ov008_0206f384(void);

void func_ov008_02066de0(void)
{
    char *context = func_ov008_02050cd4();

    if (*(int *)(context + 0x30) == 0) {
        *(int *)(context + 0x24) = 1;
        func_ov008_0206f7b0(0);
        func_ov008_0206eb64(0x14, 0, 5);
        func_ov008_0206f384();
    }
}
