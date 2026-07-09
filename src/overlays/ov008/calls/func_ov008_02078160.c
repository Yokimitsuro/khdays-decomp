extern char *func_ov008_02050cec(void);
extern void func_ov008_020778a4(char *);
void func_ov008_02078160(void)
{
    char *obj = func_ov008_02050cec();
    if (*(int *)(obj + 0x180) == 0) {
        *(int *)(obj + 0x158) = 1;
        func_ov008_020778a4(obj);
    }
}
