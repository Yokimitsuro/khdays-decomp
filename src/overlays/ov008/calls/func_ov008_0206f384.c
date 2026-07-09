extern char *func_ov008_02050cec(void);
extern int data_ov008_02090f20;
extern void func_020300f8(void *);
void func_ov008_0206f384(void)
{
    char *obj = func_ov008_02050cec();
    if (data_ov008_02090f20 != 0) {
        func_020300f8(obj + 0x154);
    }
}
