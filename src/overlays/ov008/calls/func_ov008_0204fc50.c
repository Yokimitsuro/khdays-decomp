extern int func_ov008_0204ee40(void);
extern void (*data_ov008_0208e87c[])(void);
void func_ov008_0204fc50(void)
{
    void (*callback)(void) = data_ov008_0208e87c[func_ov008_0204ee40()];
    if (callback != 0) {
        callback();
    }
}
