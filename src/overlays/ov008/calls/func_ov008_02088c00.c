extern int func_ov008_0208832c(void);
extern void func_ov008_020878c4(void);
extern void func_ov008_02088c24(void);
void *func_ov008_02088c00(void)
{
    void *result;
    if (func_ov008_0208832c() != 0) {
        result = func_ov008_02088c24;
    } else {
        result = 0;
    }
    func_ov008_020878c4();
    return result;
}
