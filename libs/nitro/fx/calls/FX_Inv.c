/* Synchronous reciprocal: start the divide and block for its result. */
extern void FX_DivAsync(int x);
extern int FX_GetDivResult(void);

int FX_Inv(int x) {
    FX_DivAsync(x);
    return FX_GetDivResult();
}
