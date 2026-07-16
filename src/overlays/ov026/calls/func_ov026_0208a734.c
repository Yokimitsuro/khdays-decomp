extern void func_02032450(void *arg0, int arg1);
extern char *data_ov026_02091368[];

void func_ov026_0208a734(void)
{
    char *base = data_ov026_02091368[0];
    int *values = (int *)(base + 0xc54c);
    void *object = *(void **)(base + 0xbfb0);

    func_02032450(object, values[0]);
    func_02032450(object, values[1]);
}
