typedef unsigned int u32;

extern char *data_ov004_02051384;

extern void func_0202f9ec(void *tileEngine);
extern void func_0202f818(void *textEngine);
extern void func_0202a7dc(void *object);
extern void func_02032428(void *manager);
extern void func_ov004_0204cae8(void *object);

void func_ov004_0205023c(void) {
    int i;
    int offset;

    if (*(int *)(data_ov004_02051384 + 0x559c) != 0) {
        func_0202f9ec(data_ov004_02051384 + 0x55ac);
        func_0202f818(data_ov004_02051384 + 0x55a0);
        *(int *)(data_ov004_02051384 + 0x559c) = 0;
    }

    i = 0;
    offset = i;
    for (; i < 10; i++) {
        func_0202a7dc(data_ov004_02051384 + offset);
        offset += 0x108;
    }

    func_02032428(data_ov004_02051384 + 0xb0c);
    func_ov004_0204cae8(data_ov004_02051384 + 0x558c);

    *(volatile u32 *)0x04000000 &= ~0xe000;
    data_ov004_02051384 = 0;
}

