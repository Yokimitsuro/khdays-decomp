extern char *data_ov008_02090fac;
extern void func_ov008_0208744c(void);
extern void func_ov008_020878c4(void);
extern void func_ov008_020896e8(void);
extern void func_ov008_02089c5c(void);

void (*func_ov008_02089728(void))(void)
{
    func_ov008_0208744c();
    func_ov008_020878c4();

    if (*(int *)(data_ov008_02090fac + 0xc56c) != 0) {
        return func_ov008_020896e8;
    }

    return func_ov008_02089c5c;
}
