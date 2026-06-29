extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_ov022_0209fb24(void);
extern void func_ov022_020a4798(void);
extern void func_ov048_020b327c(void);
extern void func_ov048_020b3934(void);

asm void func_ov048_020b3234(void)
{
    push    {r3, r4, r5, lr}
    add     r5, r0, #0
_L_0004:
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    add     r0, r5, #0
_L_000c:
    bl      func_ov048_020b327c
    add     r0, r4, #0
_L_0012:
    bl      func_ov048_020b3934
    add     r0, r4, #0
    mov     r1, #0x53
    mov     r2, #0xd5
_L_001c:
    bl      func_ov022_020a4798
    ldr     r0, [pc, #0]
    pop     {r3, r4, r5, pc}
    dcd     func_ov022_0209fb24
}
