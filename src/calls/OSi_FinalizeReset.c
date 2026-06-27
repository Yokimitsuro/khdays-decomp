extern void func_01ff8410(void);
extern void func_01ff8330(void);

extern volatile unsigned short data_02044694;

void OSi_FinalizeReset(void)
{
    while (data_02044694 == 0) { }
    *(volatile unsigned short *)0x04000208 = 0;
    func_01ff8410();
    func_01ff8330();
}
