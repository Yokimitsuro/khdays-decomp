extern void func_0202a7dc();
extern void *data_ov071_020b9a60;

void func_ov071_020b84e8(void)
{
    char *base = (char *)*(int *)&data_ov071_020b9a60 + 0x2c2c;
    int i;
    char *p;
    func_0202a7dc(base + 0xc);
    p = base + 0x120;
    i = 0;
    do {
        func_0202a7dc(p);
        i++;
        p += 0x110;
    } while (i < 6);
}
