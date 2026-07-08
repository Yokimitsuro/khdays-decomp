extern void VEC_Subtract();
extern int VEC_DotProduct();
extern int FX_Inv();
extern void VEC_MultAdd();
int func_01ffe460(int *param_1, int *param_2, int *param_3, int *param_4)
{
    int v1[3];
    int v2[3];
    unsigned int d1, d2;
    int r;
    VEC_Subtract(param_3, param_2, v1);
    VEC_Subtract(param_1, param_2, v2);
    d1 = VEC_DotProduct(v2, v1);
    if ((int)d1 < 0)
        return -1;
    d2 = VEC_DotProduct(v1, v1);
    if ((int)d1 <= (int)d2) {
        r = FX_Inv(d1, d2);
        VEC_MultAdd(r, v1, param_2, param_4);
        return r;
    }
    return -1;
}
