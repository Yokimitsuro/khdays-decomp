extern void func_0202a7dc();
extern void *data_ov033_020b4b80;

void func_ov033_020b3608(void)
{
    char *base = (char *)*(int *)&data_ov033_020b4b80 + 0x2c2c;
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
