extern int *func_02023c00(void);
extern void func_02031240(void);

void (*func_02031228(int value))(void)
{
    *func_02023c00() = value;
    return func_02031240;
}
