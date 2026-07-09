extern int func_ov008_0208832c(void);
extern void func_ov008_020878c4(void);
extern void func_ov008_0208819c(void);
void *func_ov008_02088178(void)
{
    void *result = 0;
    if (func_ov008_0208832c() != 0) {
        result = func_ov008_0208819c;
    }
    func_ov008_020878c4();
    return result;
}
