extern int data_ov106_020b8b60;
extern void func_ov002_02074024(int index, int flag);

int func_ov106_020b7728(void) {
    int active = *(int *)(data_ov106_020b8b60 + 0x8e48);

    func_ov002_02074024(0, active == 0);
    func_ov002_02074024(1, 0);
    return 0;
}
