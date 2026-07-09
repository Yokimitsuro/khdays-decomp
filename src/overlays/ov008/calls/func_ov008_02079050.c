extern void *func_ov008_02050cec(void);
extern void func_ov025_020b0888(void *context);
extern void func_ov025_020b0864(void *context);

void func_ov008_02079050(int count)
{
    void *context = func_ov008_02050cec();
    int i;
    int total;

    func_ov025_020b0888((char *)context + 0x200);

    total = count << 1;
    i = 0;
    while (i < total) {
        func_ov025_020b0864((char *)context + 0x200);
        i++;
    }
}
