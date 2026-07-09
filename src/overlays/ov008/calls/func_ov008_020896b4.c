extern char *data_ov008_02090fac;
extern void func_ov008_0208739c(void);
extern void func_ov008_02083360(void);
extern void func_ov008_020878c4(void);
extern void func_ov008_0208820c(void);

void (*func_ov008_020896b4(void))(void)
{
    func_ov008_0208739c();
    func_ov008_02083360();
    func_ov008_020878c4();
    *(int *)(data_ov008_02090fac + 0xc3d4) = 0;
    return func_ov008_0208820c;
}
