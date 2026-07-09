extern void func_ov025_02082c50();
extern void func_ov025_02082e18();
extern void func_ov025_02082fd4();
extern int data_ov025_020b5744;

void func_ov025_02084830(int arg0) {
    *(int *)(((int *)&data_ov025_020b5744)[1] + 0x95c8) = arg0;
    func_ov025_02082c50(7);
    func_ov025_02082e18(-0x10, 100);
    func_ov025_02082fd4(0);
}
