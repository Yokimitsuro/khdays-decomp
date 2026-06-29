extern void NNSi_FndGetCurrentRootHeap(void);
extern char data_ov090_020bcc00[];
extern void func_ov002_02051fc8(void);
extern void func_ov022_0209fab4(void);
extern void func_ov090_020bc6ac(void);

asm void func_ov090_020ba808(void)
{
    push    {r4, lr}
_L_0002:
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    ldr     r0, [pc, #0x30]
    mov     r1, #0x91
    lsl     r1, r1, #4
    add     r0, r4, r0
    add     r1, r4, r1
_L_0012:
    bl      func_ov002_02051fc8
    mov     r0, #0xb2
    mov     r1, #0x91
    lsl     r0, r0, #6
    lsl     r1, r1, #4
    add     r0, r4, r0
    add     r1, r4, r1
_L_0022:
    bl      func_ov002_02051fc8
    add     r0, r4, #0
_L_0028:
    bl      func_ov090_020bc6ac
    add     r0, r4, #0
_L_002e:
    bl      func_ov022_0209fab4
    ldr     r0, [pc, #0xc]
    mov     r1, #0
    str     r1, [r0, #0]
    pop     {r4, pc}
    mov     r8, r8
    cmp     r4, #0x2c
    lsl     r0, r0, #0
    dcd     data_ov090_020bcc00
}
