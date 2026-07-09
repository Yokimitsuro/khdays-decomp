extern char *data_ov008_02090fa0;
extern void func_ov008_0207b84c(int arg0);
extern void func_ov008_0207be98(void);

void (*func_ov008_0207be6c(void))(void)
{
    func_ov008_0207b84c(0);
    *(int *)(data_ov008_02090fa0 + 0x2c) = 1;
    return func_ov008_0207be98;
}
