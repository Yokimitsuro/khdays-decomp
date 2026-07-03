extern void func_0202a634(void *a, void *b, int c, int d);
extern void func_ov031_020b3e00(int a);
extern int data_ov031_020b4dc0;
extern int data_ov031_020b4d5c;

void func_ov031_020b38e0(void) {
    int obj = data_ov031_020b4dc0;
    int i = 0;
    int puVar5;
    int ibase = obj + 0x2c2c;
    puVar5 = ibase + 0x14;
    *(int *)(obj + 0x2c2c) = 0;
    *(int *)(ibase + 4) = 0;
    do {
        func_0202a634((void *)puVar5, &data_ov031_020b4d5c, 1, *(unsigned char *)(obj + 9) + 7);
        *(int *)(ibase + 0xc) = i;
        i++;
        *(int *)(ibase + 0x10) = 0;
        puVar5 += 0x118;
        ibase += 0x118;
    } while (i < 2);
    func_ov031_020b3e00(obj);
}
