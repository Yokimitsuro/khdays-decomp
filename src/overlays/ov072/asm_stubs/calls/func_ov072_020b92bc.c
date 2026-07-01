extern void NNSi_FndAllocFromDefaultExpHeap(void);
extern char data_0204c4d8[];
extern char data_ov072_020ba618[];
extern char data_ov072_020ba638[];
extern char data_ov072_020ba648[];
extern char data_ov072_020ba658[];
extern void func_02014e18(void);
extern void func_02016f10(void);
extern void func_020358f4(void);
extern void func_ov022_020911f0(void);
extern void func_ov022_02091298(void);
extern void func_ov072_020b95ec(void);

asm void func_ov072_020b92bc(void)
{
    push    {r3, r4, r5, r6, r7, lr}
    sub     sp, #0xf8
    add     r5, r0, #0
    ldr     r0, [pc, #0x1e8]
    add     r1, r5, r0
    ldr     r0, [r1, #0x14]
    ldrb    r4, [r1, #0x13]
    asr     r6, r0, #0xc
    mov     r0, #0x60
_L_0012:
    bl      NNSi_FndAllocFromDefaultExpHeap
    ldr     r1, [pc, #0x1dc]
    mov     r2, #1
    str     r0, [r5, r1]
    ldr     r0, [r5, r1]
    mov     r1, #0
_L_0020:
    bl      func_ov022_020911f0
    mov     r3, #0
    mov     r0, #1
    str     r0, [sp, #0xc]
    ldr     r1, [pc, #0x1cc]
    str     r3, [sp, #8]
    add     r0, sp, #8
    strh    r1, [r0, #0xa]
    ldr     r0, [pc, #0x1c8]
    add     r1, #0x52
    str     r0, [sp, #0x18]
    mov     r0, #0xa
    lsl     r0, r0, #0xc
    str     r0, [sp, #0x1c]
    mov     r0, #0x1e
    lsl     r0, r0, #0xc
    str     r0, [sp, #0x20]
    mov     r0, #1
    lsl     r0, r0, #0xd
    str     r0, [sp, #0x24]
    mov     r0, #3
    lsl     r0, r0, #0xc
    str     r1, [sp, #0x14]
    str     r0, [sp, #0x28]
    mov     r1, #1
    add     r1, #0xff
    lsr     r0, r0, #4
    str     r0, [sp, #0x38]
    mov     r0, #4
    str     r0, [sp, #0x40]
    mov     r0, #2
    str     r3, [sp, #0x30]
    str     r1, [sp, #0x34]
    str     r1, [sp, #0x3c]
    add     r2, sp, #0x48
    strb    r6, [r2, #0xc]
    mov     r1, #1
    str     r1, [sp, #0x5c]
    str     r0, [sp, #0x58]
    strh    r3, [r2, #0x1a]
    lsl     r2, r0, #8
    lsl     r1, r0, #0xa
    str     r1, [sp, #0x64]
    ldr     r1, [pc, #0x184]
    lsl     r7, r0, #9
    str     r1, [sp, #0x68]
    mov     r1, #0x19
    lsl     r1, r1, #0xc
    str     r1, [sp, #0x6c]
    mov     r1, #0x1e
    lsl     r1, r1, #0xc
    str     r1, [sp, #0x70]
    lsl     r1, r0, #0xb
    mov     r0, #4
    str     r1, [sp, #0x74]
    str     r0, [sp, #0x90]
    str     r3, [sp, #0x78]
    str     r3, [sp, #0x80]
    str     r2, [sp, #0x84]
    str     r7, [sp, #0x88]
    str     r2, [sp, #0x8c]
    mov     r1, #6
    add     r0, sp, #0x88
    strb    r1, [r0, #0x1c]
    mov     r0, #1
    str     r0, [sp, #0xac]
    str     r3, [sp, #0xa8]
    add     r0, sp, #0x88
    strh    r3, [r0, #0x2a]
    ldr     r0, [pc, #0x154]
    str     r3, [sp, #0xc8]
    str     r0, [sp, #0xb4]
    ldr     r0, [pc, #0x154]
    str     r3, [sp, #0xd0]
    str     r0, [sp, #0xb8]
    mov     r0, #0xa
    lsl     r0, r0, #0xc
    lsr     r0, r0, #1
    str     r0, [sp, #0xbc]
    mov     r0, #0x1e
    lsl     r0, r0, #0xc
    str     r0, [sp, #0xc0]
    lsl     r0, r1, #0xb
    str     r0, [sp, #0xc4]
    mov     r0, #4
    str     r0, [sp, #0xe0]
    str     r2, [sp, #0xd4]
    str     r7, [sp, #0xd8]
    str     r2, [sp, #0xdc]
    mov     r1, #0xa
    add     r0, sp, #0xe8
    strb    r1, [r0, #0xc]
    ldrb    r0, [r5, #9]
    mov     r1, #0x30
_L_00de:
    bl      func_020358f4
    cmp     r0, #0
    beq     _L_00fa
    ldr     r1, [sp, #8]
    mov     r0, #1
    orr     r1, r0
    str     r1, [sp, #8]
    ldr     r1, [sp, #0x58]
    orr     r1, r0
    str     r1, [sp, #0x58]
    ldr     r1, [sp, #0xa8]
    orr     r0, r1
    str     r0, [sp, #0xa8]
_L_00fa:
    mov     r0, #3
    str     r0, [sp, #0]
    ldr     r2, [pc, #0x10c]
    str     r6, [sp, #4]
    ldr     r3, [r5, r2]
    mov     r2, #2
    lsl     r2, r2, #0xe
    add     r2, r3, r2
    ldr     r7, [pc, #0x104]
    mov     r3, #2
    and     r2, r7
    ldr     r0, [pc, #0xe0]
    lsl     r2, r2, #7
    lsl     r3, r3, #0x1e
    orr     r2, r3
    add     r4, #0x8c
    lsr     r3, r7, #0xf
    and     r3, r4
    orr     r2, r3
    ldr     r0, [r5, r0]
    add     r1, r5, #0
    add     r3, sp, #8
_L_0126:
    bl      func_ov022_02091298
    ldr     r1, [pc, #0xe8]
    mov     r0, #0x10
    ldrsb   r1, [r1, r0]
    cmp     r1, #0
    blt     _L_013a
    ldr     r0, [pc, #0xbc]
    ldr     r0, [r5, r0]
    strb    r1, [r0, #0x18]
_L_013a:
    mov     r4, #0
    mov     r7, #3
    b       _L_0160
_L_0140:
    ldr     r0, [pc, #0xb0]
    mov     r2, #0
    ldr     r0, [r5, r0]
    mov     r3, #6
    ldr     r1, [r0, #0xc]
    mov     r0, #0x72
    lsl     r0, r0, #2
    mul     r0, r4
    add     r0, r1, r0
    str     r0, [r0, #0x74]
    ldr     r1, [pc, #0xc0]
    add     r0, #0x48
    str     r7, [sp, #0]
_L_015a:
    bl      func_02014e18
    add     r4, r4, #1
_L_0160:
    cmp     r4, r6
    blt     _L_0140
    ldr     r0, [pc, #0x8c]
    ldr     r0, [r5, r0]
    ldr     r4, [r0, #0xc]
    ldr     r0, [r4, #0x4c]
    cmp     r0, #0
    beq     _L_0174
    add     r0, #0x40
    b       _L_0176
_L_0174:
    mov     r0, #0
_L_0176:
    cmp     r0, #0
    beq     _L_0182
    ldr     r1, [pc, #0xa0]
_L_017c:
    bl      func_02016f10
    b       _L_0186
_L_0182:
    mov     r0, #0
    mvn     r0, r0
_L_0186:
    ldr     r1, [pc, #0x98]
    str     r0, [r5, r1]
    ldr     r0, [r4, #0x4c]
    cmp     r0, #0
    beq     _L_0194
    add     r0, #0x40
    b       _L_0196
_L_0194:
    mov     r0, #0
_L_0196:
    cmp     r0, #0
    beq     _L_01a2
    ldr     r1, [pc, #0x88]
_L_019c:
    bl      func_02016f10
    b       _L_01a6
_L_01a2:
    mov     r0, #0
    mvn     r0, r0
_L_01a6:
    ldr     r1, [pc, #0x80]
    str     r0, [r5, r1]
    ldr     r0, [r4, #0x4c]
    cmp     r0, #0
    beq     _L_01b4
    add     r0, #0x40
    b       _L_01b6
_L_01b4:
    mov     r0, #0
_L_01b6:
    cmp     r0, #0
    beq     _L_01c2
    ldr     r1, [pc, #0x70]
_L_01bc:
    bl      func_02016f10
    b       _L_01c6
_L_01c2:
    mov     r0, #0
    mvn     r0, r0
_L_01c6:
    ldr     r1, [pc, #0x68]
    str     r0, [r5, r1]
    ldr     r0, [r4, #0x4c]
    cmp     r0, #0
    beq     _L_01d4
    add     r0, #0x40
    b       _L_01d6
_L_01d4:
    mov     r0, #0
_L_01d6:
    cmp     r0, #0
    beq     _L_01e2
    ldr     r1, [pc, #0x58]
_L_01dc:
    bl      func_02016f10
    b       _L_01e6
_L_01e2:
    mov     r0, #0
    mvn     r0, r0
_L_01e6:
    ldr     r1, [pc, #0x50]
    str     r0, [r5, r1]
    add     sp, #0xf8
    pop     {r3, r4, r5, r6, r7, pc}
    mov     r8, r8
    lsr     r0, r3, #4
    lsl     r0, r0, #0
    mov     r6, #0x44
    lsl     r0, r0, #0
    lsl     r1, r4, #0xb
    lsl     r0, r0, #0
    lsr     r5, r1, #0x13
    lsl     r0, r0, #0
    asr     r3, r6, #0xc
    lsl     r0, r0, #0
    lsr     r3, r6, #0xc
    lsl     r0, r0, #0
    lsr     r6, r4, #0x19
    lsl     r0, r0, #0
    cmp     r3, #0xd0
    lsl     r0, r0, #0
    dcd     0x00fffffc
    dcd     data_0204c4d8
    dcd     func_ov072_020b95ec
    dcd     data_ov072_020ba648
    dcd     0x00002e68
    dcd     data_ov072_020ba658
    dcd     0x00002e6c
    dcd     data_ov072_020ba638
    dcd     0x00002e70
    dcd     data_ov072_020ba618
    dcd     0x00002e74
}
