extern void func_ov100_020bc004(void);
extern void srand_0x0208875c(void);

asm void func_ov100_020ba7c0(void)
{
    dcd     0xe59fc004
    dcd     0xe59f0004
    dcd     0xe12fff1c
    dcd     srand_0x0208875c
    dcd     func_ov100_020bc004
}
