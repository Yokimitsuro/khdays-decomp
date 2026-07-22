/* ITCM twin of FX_Inv over FX_InvAsync. */
extern void FX_InvAsync(int x);
extern int FX_GetDivResult(void);

int FX_Inv_0x01ff8a40(int x) {
    FX_InvAsync(x);
    return FX_GetDivResult();
}
