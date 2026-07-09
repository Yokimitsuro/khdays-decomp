extern void func_ov008_0205bea0(void *, void *, int);
void func_ov008_0205c54c(void *arg0, void *arg1, int fast)
{
    int delay = 0x3e8;
    if (fast != 0) {
        delay = 0x1f4;
    }
    func_ov008_0205bea0(arg0, arg1, delay);
}
