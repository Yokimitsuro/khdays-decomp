extern int FX_GetDivResult();
extern int FX_DivAsync();

void FX_Inv(void)
{
    FX_DivAsync();
    FX_GetDivResult();
}
