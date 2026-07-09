extern int func_ov008_02050c3c(void);
extern int func_ov008_02055808(int, int);
extern void func_ov008_0205589c(int, int);
void func_ov008_02070b20(void)
{
    int base = func_ov008_02050c3c();
    func_ov008_0205589c(base, func_ov008_02055808(base, 0x42));
}
