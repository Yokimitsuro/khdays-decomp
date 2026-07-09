extern int func_ov025_02084b14();
extern int func_ov025_02084a8c();
extern int data_ov025_020b575c;
extern int func_ov025_0208843c();
extern void func_ov025_0208884c();

void func_ov025_020a4c30(void) {
    int x = func_ov025_02084b14();
    int a = func_ov025_02084a8c();
    if (data_ov025_020b575c == 0) return;
    if (*(int *)(x + 0x44) != 1) return;
    func_ov025_0208884c(a, func_ov025_0208843c(a, 0x47), 1);
}
