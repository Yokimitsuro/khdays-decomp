extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_0202a440(void *p);
extern void NNSi_FndFreeFromDefaultHeap(void *p);
extern void WM_EndKeySharing_0x02023ad0(void *p);
extern void func_ov002_02051fc8(void *a, void *b);
extern void func_ov030_020b4c34(void *p);
extern void func_ov022_0209fab4(void *p);
extern void *data_0204c240;

asm void func_ov030_020b3310(void)
{
    push    {r4, lr}
    bl      NNSi_FndGetCurrentRootHeap
    mov     r4, r0
    ldr     r0, =data_0204c240
    ldrb    r1, [r0, #0]
    mov     r0, #0x4
    tst     r0, r1
    bne     _L_22
    ldr     r0, =0x2c2c
    add     r0, r4, r0
    bl      func_0202a440
    ldr     r0, =0x2c50
    ldr     r0, [r4, r0]
    bl      NNSi_FndFreeFromDefaultHeap
_L_22:
    ldr     r0, =0x2cac
    ldr     r0, [r4, r0]
    cmp     r0, #0
    beq     _L_2e
    bl      WM_EndKeySharing_0x02023ad0
_L_2e:
    ldr     r0, =0x2c54
    mov     r1, #0x91
    lsl     r1, r1, #0x4
    add     r0, r4, r0
    add     r1, r4, r1
    bl      func_ov002_02051fc8
    ldr     r0, =0x2cb0
    add     r0, r4, r0
    bl      func_ov030_020b4c34
    mov     r0, r4
    bl      func_ov022_0209fab4
    pop     {r4, pc}
}
