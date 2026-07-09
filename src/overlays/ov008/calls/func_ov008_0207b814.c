extern int OS_IsTickAvailable_0x01ff8138(void);
extern void func_ov008_0207bc94(short *);
void func_ov008_0207b814(void)
{
    short value = OS_IsTickAvailable_0x01ff8138();
    func_ov008_0207bc94(&value);
}
