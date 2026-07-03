extern void func_0202a634();
extern void *data_ov051_020b7380;
extern void *data_ov051_020b734c;
extern void *data_ov051_020b7360;

void func_ov051_020b5d6c(void)
{
    int i;
    char *slot;
    char *base;
    int zero;
    char *obj = (char *)*(int *)&data_ov051_020b7380;
    base = obj + 0x2c2c;
    *(int *)(obj + 0x2c2c) = 0;
    *(int *)(base + 4) = 0;
    *(int *)(base + 8) = 0;
    func_0202a634(base + 0xc, &data_ov051_020b734c, 1, ((unsigned char *)obj)[9] + 7);
    i = 0;
    slot = base + 0x120;
    zero = 0;
    do {
        func_0202a634(slot, &data_ov051_020b7360, 1, ((unsigned char *)obj)[9] + 7);
        *(int *)(base + 0x11c) = 0x1c - i;
        i++;
        *(int *)(base + 0x118) = zero;
        slot += 0x110;
        base += 0x110;
    } while (i < 6);
}
