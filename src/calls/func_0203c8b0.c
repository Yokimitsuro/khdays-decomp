extern void func_0201f390(int x);
void func_0203c8b0(int param_1) {
    if (*(void **)(param_1 + 0x7c) == 0) return;
    func_0201f390(0);
    (*(void (**)(int))(param_1 + 0x7c))(param_1);
    func_0201f390(1);
}
