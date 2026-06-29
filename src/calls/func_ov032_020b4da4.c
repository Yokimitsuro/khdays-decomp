extern char data_ov032_020b5890[];
extern void func_ov022_020911f0(void);
extern void func_ov022_02091298(void);

asm void func_ov032_020b4da4(void)
{
    push    {r3, r4, r5, r6, r7, lr}
    sub     sp, #0xa8
    add     r4, r0, #0
    ldr     r0, [pc, #0x98]
    mov     r1, #1
    ldr     r0, [r4, r0]
    add     r2, r1, #0
    add     r0, #0x30
_L_0010:
    bl      func_ov022_020911f0
    mov     r6, #1
    ldr     r0, [pc, #0x8c]
    mov     r7, #3
    str     r0, [sp, #8]
    mov     r3, #0x19
    lsl     r3, r3, #0xc
    add     r1, r6, #0
    str     r6, [sp, #0xc]
    mov     r5, #0
    add     r0, sp, #8
    strh    r5, [r0, #0xa]
    add     r1, #0xff
    ldr     r0, [pc, #0x78]
    lsl     r7, r7, #0xc
    str     r0, [sp, #0x14]
    ldr     r0, [pc, #0x78]
    lsl     r2, r3, #1
    str     r0, [sp, #0x18]
    lsr     r0, r7, #4
    str     r0, [sp, #0x38]
    mov     r0, #5
    str     r0, [sp, #0x40]
    str     r3, [sp, #0x1c]
    str     r2, [sp, #0x20]
    str     r7, [sp, #0x24]
    str     r5, [sp, #0x28]
    str     r5, [sp, #0x30]
    str     r1, [sp, #0x34]
    str     r1, [sp, #0x3c]
    mov     r1, #4
    add     r0, sp, #0x48
    strb    r1, [r0, #0xc]
    ldr     r0, [pc, #0x58]
    str     r6, [sp, #0x5c]
    str     r0, [sp, #0x58]
    add     r6, sp, #0x48
    strh    r5, [r6, #0x1a]
    mov     r6, #5
    lsl     r6, r6, #0xa
    add     r0, #0x7d
    str     r6, [sp, #0x64]
    lsl     r6, r1, #0xa
    str     r2, [sp, #0x70]
    lsl     r2, r1, #7
    str     r0, [sp, #0x88]
    mov     r0, #0x25
    str     r3, [sp, #0x6c]
    str     r0, [sp, #0x90]
    str     r6, [sp, #0x68]
    str     r7, [sp, #0x74]
    str     r5, [sp, #0x78]
    str     r5, [sp, #0x80]
    str     r2, [sp, #0x84]
    str     r2, [sp, #0x8c]
    add     r0, sp, #0x88
    strb    r1, [r0, #0x1c]
    mov     r0, #2
    str     r0, [sp, #0]
    str     r1, [sp, #4]
    ldr     r0, [pc, #0x14]
    ldr     r2, [pc, #0x24]
    ldr     r0, [r4, r0]
    add     r1, r4, #0
    add     r0, #0x30
    add     r3, sp, #8
_L_0096:
    bl      func_ov022_02091298
    add     sp, #0xa8
    pop     {r3, r4, r5, r6, r7, pc}
    mov     r8, r8
    mov     r6, #0x44
    lsl     r0, r0, #0
    lsl     r1, r0, #6
    lsl     r0, r0, #0
    lsr     r2, r3, #6
    lsl     r0, r0, #0
    asr     r2, r3, #6
    lsl     r0, r0, #0
    lsl     r3, r0, #0xe
    lsl     r0, r0, #0
    dcd     data_ov032_020b5890
}
