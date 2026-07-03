extern void func_0202a634();
extern void *data_ov033_020b4b80;
extern void *data_ov033_020b4b4c;
extern void *data_ov033_020b4b60;

void func_ov033_020b356c(void)
{
    int i;
    char *slot;
    char *base;
    int zero;
    char *obj = (char *)*(int *)&data_ov033_020b4b80;
    base = obj + 0x2c2c;
    *(int *)(obj + 0x2c2c) = 0;
    *(int *)(base + 4) = 0;
    *(int *)(base + 8) = 0;
    func_0202a634(base + 0xc, &data_ov033_020b4b4c, 1, ((unsigned char *)obj)[9] + 7);
    i = 0;
    slot = base + 0x120;
    zero = 0;
    do {
        func_0202a634(slot, &data_ov033_020b4b60, 1, ((unsigned char *)obj)[9] + 7);
        *(int *)(base + 0x11c) = 0x1c - i;
        i++;
        *(int *)(base + 0x118) = zero;
        slot += 0x110;
        base += 0x110;
    } while (i < 6);
}
