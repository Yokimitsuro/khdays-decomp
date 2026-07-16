extern int func_ov008_02050cec();
extern int func_ov008_02050c64();
extern int data_ov008_02090f20;
extern int func_ov008_02054788();
extern void func_ov008_02054ba4();

void func_ov008_0206f694(void) {
    int x = func_ov008_02050cec();
    int a = func_ov008_02050c64();
    if (data_ov008_02090f20 == 0) return;
    if (*(int *)(x + 0x44) != 0) return;
    func_ov008_02054ba4(a, func_ov008_02054788(a, 0x48), 1);
}
