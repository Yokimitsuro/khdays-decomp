extern void FX_DivAsync(void);
extern void FX_GetDivResult(void);

asm void FX_Inv(void)
{
    stmdb sp!, {r3, lr}
    bl FX_DivAsync
    bl FX_GetDivResult
    ldmia sp!, {r3, pc}
}
