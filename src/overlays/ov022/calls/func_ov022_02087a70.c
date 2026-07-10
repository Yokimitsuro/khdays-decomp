extern int data_ov022_020b2e78;
extern int func_ov002_0206aaa0(void);
extern int func_ov022_0208a278(void);
extern void func_ov022_02087890(int arg0, int arg1);

void func_ov022_02087a70(void) {
    int obj = *(int *)((char *)&data_ov022_020b2e78 + 4);
    int slot;
    int g;
    int save;
    if (*(int *)(obj + 0x10) == 0) return;
    if (func_ov002_0206aaa0() == 0) return;
    slot = *(int *)(*(int *)(obj + 0x10) + 0x20);
    g = func_ov022_0208a278();
    save = *(unsigned char *)(g + 0x10);
    func_ov022_02087890(slot, 0);
    *(unsigned char *)(g + 0x10) = save;
}
