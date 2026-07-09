extern void func_ov036_020b3b40();
struct b1_694 { unsigned char b : 1; };
void func_ov036_020b3990(int param_1, int param_2)
{
    if (!((struct b1_694 *)(param_1 + 0x694))->b)
        return;
    func_ov036_020b3b40(param_1, param_2 + 0x14);
}
