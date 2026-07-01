extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_02020a9c(void);
extern void func_ov022_0209fb24(void);
extern void func_ov022_020a4798(void);
extern void func_ov035_020b32a0(void);
extern void func_ov035_020b3a30(void);

asm void func_ov035_020b3234(void)
{
    push    {r3, r4, r5, lr}
    add     r5, r0, #0
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    add     r0, r5, #0
_L_000c:
    bl      func_ov035_020b32a0
_L_0010:
    bl      func_02020a9c
    cmp     r0, #0x2a
    beq     _L_001e
    add     r0, r4, #0
_L_001a:
    bl      func_ov035_020b3a30
_L_001e:
    add     r0, r4, #0
    mov     r1, #0x47
    mov     r2, #0xd3
_L_0024:
    bl      func_ov022_020a4798
    ldr     r0, [pc, #0]
    pop     {r3, r4, r5, pc}
    dcd     func_ov022_0209fb24
}
