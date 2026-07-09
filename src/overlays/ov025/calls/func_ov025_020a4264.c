extern int data_ov025_020b575c;
extern int func_ov025_02084a8c();
extern int func_ov025_0208843c();
extern void func_ov025_0208884c();

void func_ov025_020a4264(void) {
    if (data_ov025_020b575c == 0) return;
    int a = func_ov025_02084a8c();
    int i = 0xc9;
    do {
        func_ov025_0208884c(a, func_ov025_0208843c(a, i), 0);
        i++;
    } while (i <= 0xdc);
}
