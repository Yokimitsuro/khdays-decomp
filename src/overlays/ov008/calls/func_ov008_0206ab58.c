extern char *func_ov008_02050cd4(void);
extern void func_02033b78(int arg0, int arg1);
extern void func_ov008_0206b37c(int arg0);

void func_ov008_0206ab58(void)
{
    char *context = func_ov008_02050cd4();

    func_02033b78(0, 2);
    func_ov008_0206b37c((short)(*(short *)context - 1));
}
