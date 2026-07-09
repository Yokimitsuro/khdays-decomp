extern void func_ov074_020b8af8();
struct b1_694 { unsigned char b : 1; };
void func_ov074_020b8a04(int param_1, int param_2)
{
    if (!((struct b1_694 *)(param_1 + 0x694))->b)
        return;
    func_ov074_020b8af8(param_1, param_2 + 0x10);
}
