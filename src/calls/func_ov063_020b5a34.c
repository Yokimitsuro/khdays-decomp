extern void NNSi_FndGetCurrentRootHeap(void);
extern char data_0204c240[];
extern char data_ov063_020b7d14[];
extern void func_0201ef9c(void);
extern void func_0202a3cc(void);
extern void func_ov022_0209fb24(void);
extern void func_ov022_020a4798(void);
extern void func_ov063_020b5b14(void);
extern void func_ov063_020b6fd0(void);

asm void func_ov063_020b5a34(void)
{
    push    {r3, r4, r5, lr}
    add     r5, r0, #0
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    add     r0, r5, #0
_L_000c:
    bl      func_ov063_020b5b14
    ldr     r0, [pc, #0x54]
    ldrb    r1, [r0, #0]
    mov     r0, #4
    tst     r0, r1
    bne     _L_004e
    ldr     r1, [r5, #0]
    ldr     r0, [pc, #0x4c]
    add     r1, r1, #7
_L_0020:
    bl      func_0201ef9c
    ldr     r2, [pc, #0x48]
    str     r0, [r4, r2]
    add     r0, r2, #0
    ldr     r1, [r4, #0x20]
    ldr     r3, [r5, #0]
    sub     r0, #0x24
    ldr     r2, [r4, r2]
    add     r0, r4, r0
    add     r1, r1, #4
    add     r3, r3, #7
_L_0038:
    bl      func_0202a3cc
    mov     r0, #0
    ldr     r2, [pc, #0x34]
    mvn     r0, r0
    str     r0, [r4, r2]
    sub     r2, #0x58
    ldr     r2, [r4, r2]
    add     r0, r4, #0
    mov     r1, #0
    blx     r2
_L_004e:
    ldr     r1, [pc, #0x28]
    add     r0, r4, #0
    add     r1, r4, r1
_L_0054:
    bl      func_ov063_020b6fd0
    add     r0, r4, #0
    mov     r1, #0x50
    mov     r2, #0xd1
_L_005e:
    bl      func_ov022_020a4798
    ldr     r0, [pc, #0x18]
    pop     {r3, r4, r5, pc}
    mov     r8, r8
    dcd     data_0204c240
    dcd     data_ov063_020b7d14
    dcd     0x00002c50
    dcd     0x000006bc
    dcd     0x00002ca8
    dcd     func_ov022_0209fb24
}
