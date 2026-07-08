extern void func_0201d0e0();
extern void func_0201e144();
void func_0201d088(int param_1, int param_2)
{
    int field = *(int *)(param_1 + 0x110);
    int bit = (field << 0x1e) >> 0x1f;
    if (bit == 0) {
        func_0201d0e0(param_1, bit, param_2, field);
        return;
    }
    if (param_2 == 0) {
        func_0201d0e0(param_1, bit, param_2, field);
        return;
    }
    func_0201e144((int *)(param_1 + 0xe8), 0, param_2);
    *(unsigned int *)(param_1 + 0x110) |= 8;
    *(int *)(param_1 + 0x150) = 0;
}
