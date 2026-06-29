extern char data_ov056_020b7620[];
extern void func_ov022_0209fb60(void);
extern void func_ov022_0209fb98(void);
extern void func_ov056_020b6134(void);

asm void func_ov056_020b5cc8(void)
{
    push    {r4, lr}
    ldr     r0, [pc, #0x5c]
    mov     r1, #0
    ldr     r4, [r0, #0]
    mov     r2, #1
    add     r0, r4, #0
_L_000c:
    bl      func_ov022_0209fb60
    add     r0, r4, #0
    mov     r1, #0
    mov     r2, #1
_L_0016:
    bl      func_ov022_0209fb98
    ldr     r1, [pc, #0x48]
    ldrsb   r0, [r4, r1]
    cmp     r0, #0
    beq     _L_002e
    sub     r0, r1, #1
    ldrb    r2, [r4, r0]
    mov     r0, #1
    orr     r2, r0
    sub     r0, r1, #1
    strb    r2, [r4, r0]
_L_002e:
    add     r0, r4, #0
    mov     r1, #1
    mov     r2, #2
_L_0034:
    bl      func_ov022_0209fb60
    mov     r1, #1
    add     r0, r4, #0
    add     r2, r1, #0
_L_003e:
    bl      func_ov022_0209fb98
    ldr     r1, [pc, #0x24]
    ldrsb   r0, [r4, r1]
    cmp     r0, #0
    beq     _L_0056
    sub     r0, r1, #1
    ldrb    r2, [r4, r0]
    mov     r0, #1
    orr     r2, r0
    sub     r0, r1, #1
    strb    r2, [r4, r0]
_L_0056:
    add     r0, r4, #0
_L_0058:
    bl      func_ov056_020b6134
    pop     {r4, pc}
    mov     r8, r8
    dcd     data_ov056_020b7620
    dcd     0x00000da9
    dcd     0x00000f0d
}
