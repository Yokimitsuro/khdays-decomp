extern void FX_InvAsync(void);
extern void FX_GetDivResult(void);

asm void FX_Inv_0x01ff8a40(void)
{
    stmdb sp!, {r3, lr}
    bl FX_InvAsync
    bl FX_GetDivResult
    ldmia sp!, {r3, pc}
}
