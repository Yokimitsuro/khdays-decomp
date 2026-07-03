extern void func_0202a634();
extern void *data_ov071_020b9a60;
extern void *data_ov071_020b9a2c;
extern void *data_ov071_020b9a40;

void func_ov071_020b844c(void)
{
    int i;
    char *slot;
    char *base;
    int zero;
    char *obj = (char *)*(int *)&data_ov071_020b9a60;
    base = obj + 0x2c2c;
    *(int *)(obj + 0x2c2c) = 0;
    *(int *)(base + 4) = 0;
    *(int *)(base + 8) = 0;
    func_0202a634(base + 0xc, &data_ov071_020b9a2c, 1, ((unsigned char *)obj)[9] + 7);
    i = 0;
    slot = base + 0x120;
    zero = 0;
    do {
        func_0202a634(slot, &data_ov071_020b9a40, 1, ((unsigned char *)obj)[9] + 7);
        *(int *)(base + 0x11c) = 0x1c - i;
        i++;
        *(int *)(base + 0x118) = zero;
        slot += 0x110;
        base += 0x110;
    } while (i < 6);
}
