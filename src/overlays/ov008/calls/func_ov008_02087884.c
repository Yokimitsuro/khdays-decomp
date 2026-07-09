extern void func_02032450(void *arg0, int arg1);
extern char *data_ov008_02090fac[];

void func_ov008_02087884(void)
{
    char *base = data_ov008_02090fac[0];
    int *values = (int *)(base + 0xc54c);
    void *object = *(void **)(base + 0xbfb0);

    func_02032450(object, values[0]);
    func_02032450(object, values[1]);
}
