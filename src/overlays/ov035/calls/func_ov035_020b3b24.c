extern void func_ov035_020b3c18();
struct b1_694 { unsigned char b : 1; };
void func_ov035_020b3b24(int param_1, int param_2)
{
    if (!((struct b1_694 *)(param_1 + 0x694))->b)
        return;
    func_ov035_020b3c18(param_1, param_2 + 0x10);
}
