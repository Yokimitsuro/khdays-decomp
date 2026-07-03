extern void func_0202a634(int a, void *b, int c, int d);
extern void func_0202accc(int a, int b, int c, int d);
extern int *data_ov090_020bcc00;
extern int data_ov090_020bcbd4[];
void func_ov090_020bc654(void) {
    int obj = (int)data_ov090_020bcc00;
    int base = obj + 0x2ce4;
    *(int *)(base + 0x24) = 0;
    *(int *)base = 0;
    *(int *)(base + 0x10) = 0;
    *(int *)(base + 0xc) = 0;
    func_0202a634(base + 0x28, data_ov090_020bcbd4, 1, *(unsigned char *)(obj + 9) + 7);
    func_0202accc(base + 0x28, 0, base + 0x108, 0);
    func_0202accc(base + 0x28, 2, base + 0x108, 0);
}
