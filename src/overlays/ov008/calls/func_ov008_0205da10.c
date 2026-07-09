extern void *func_ov008_02054788(void *arg0, void *arg1, int arg2);
extern void func_ov008_02054b18(void *arg0, void *arg1, int arg2);
extern void func_ov008_02054ba4(void *arg0, void *arg1, int arg2);

void func_ov008_0205da10(void *arg0, void *arg1, int arg2)
{
    void *value = func_ov008_02054788(arg0, arg1, arg2);

    func_ov008_02054b18(arg0, value, arg2 == 0);
    func_ov008_02054ba4(arg0, value, arg2);
}
