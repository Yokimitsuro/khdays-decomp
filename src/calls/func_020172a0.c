extern void func_02017584();
void func_020172a0(unsigned int *param_1, unsigned int *param_2, int param_3)
{
    int v = (int)*param_2;
    int limit = (unsigned int)*(unsigned short *)(param_2[2] + 4) * 0x1000;
    if (v >= limit)
        v = limit - 1;
    else if (v < 0)
        v = 0;
    func_02017584(param_2[2], param_3, v, param_1);
}
