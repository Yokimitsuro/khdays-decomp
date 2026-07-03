extern void func_0202a634(void *a, void *b, int c, int d);
extern void func_ov088_020bb3a0(int a);
extern int data_ov088_020bc360;
extern int data_ov088_020bc2fc;

void func_ov088_020bae80(void) {
    int obj = data_ov088_020bc360;
    int i = 0;
    int puVar5;
    int ibase = obj + 0x2c2c;
    puVar5 = ibase + 0x14;
    *(int *)(obj + 0x2c2c) = 0;
    *(int *)(ibase + 4) = 0;
    do {
        func_0202a634((void *)puVar5, &data_ov088_020bc2fc, 1, *(unsigned char *)(obj + 9) + 7);
        *(int *)(ibase + 0xc) = i;
        i++;
        *(int *)(ibase + 0x10) = 0;
        puVar5 += 0x118;
        ibase += 0x118;
    } while (i < 2);
    func_ov088_020bb3a0(obj);
}
