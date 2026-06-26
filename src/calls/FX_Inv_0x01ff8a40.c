extern int FX_GetDivResult();
extern int FX_InvAsync();

void FX_Inv_0x01ff8a40(void) {
    FX_InvAsync();
    FX_GetDivResult();
}
