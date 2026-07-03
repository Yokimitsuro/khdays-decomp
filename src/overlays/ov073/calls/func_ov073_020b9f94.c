extern void func_0202a634(int a, void *b, int c, int d);
extern void func_0202accc(int a, int b, int c, int d);
extern int *data_ov073_020ba540;
extern int data_ov073_020ba514[];
void func_ov073_020b9f94(void) {
    int obj = (int)data_ov073_020ba540;
    int base = obj + 0x2ce4;
    *(int *)(base + 0x24) = 0;
    *(int *)base = 0;
    *(int *)(base + 0x10) = 0;
    *(int *)(base + 0xc) = 0;
    func_0202a634(base + 0x28, data_ov073_020ba514, 1, *(unsigned char *)(obj + 9) + 7);
    func_0202accc(base + 0x28, 0, base + 0x108, 0);
    func_0202accc(base + 0x28, 2, base + 0x108, 0);
}
