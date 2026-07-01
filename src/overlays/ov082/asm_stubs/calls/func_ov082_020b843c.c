extern char data_0204c240[];
extern char data_ov082_020ba45c[];
extern char data_ov082_020ba500[];
extern void func_02023588(void);
extern void func_02024ee8(void);
extern void func_02024fd4(void);
extern void func_ov002_02051d6c(void);
extern void func_ov002_02051eec(void);
extern void func_ov022_0209fb60(void);

asm void func_ov082_020b843c(void)
{
    push    {r3, r4, r5, r6, r7, lr}
    add     r5, r0, #0
    ldr     r0, [pc, #0x78]
    mov     r6, #1
    ldr     r4, [r0, #0]
    ldr     r0, [pc, #0x78]
    ldr     r7, [r5, r0]
    ldr     r0, [pc, #0x78]
    ldrb    r1, [r0, #0]
    mov     r0, #4
    tst     r0, r1
    bne     _L_0024
    ldr     r0, [pc, #0x70]
_L_001a:
    bl      func_02023588
    cmp     r0, #0
    beq     _L_0024
    mov     r6, #0
_L_0024:
    ldr     r0, [pc, #0x68]
    mov     r1, #6
_L_0028:
    bl      func_02024ee8
    ldr     r1, [pc, #0x54]
    cmp     r6, #0
    str     r0, [r5, r1]
    beq     _L_0078
    add     r0, r4, #0
    mov     r1, #1
    mov     r2, #2
_L_003a:
    bl      func_ov022_0209fb60
    ldr     r1, [pc, #0x54]
    ldrsb   r0, [r4, r1]
    cmp     r0, #0
    beq     _L_0052
    sub     r0, r1, #1
    ldrb    r2, [r4, r0]
    mov     r0, #1
    orr     r2, r0
    sub     r0, r1, #1
    strb    r2, [r4, r0]
_L_0052:
    ldr     r0, [pc, #0x44]
    ldr     r1, [pc, #0x44]
    mov     r2, #0x91
    lsl     r2, r2, #4
    add     r0, r4, r0
    add     r1, r4, r1
    add     r2, r5, r2
_L_0060:
    bl      func_ov002_02051d6c
    mov     r0, #0x78
    str     r0, [sp, #0]
    ldr     r0, [pc, #0x2c]
    ldr     r1, [pc, #0x30]
    ldrb    r3, [r5, #9]
    add     r0, r5, r0
    add     r1, r4, r1
    add     r2, r7, #0
_L_0074:
    bl      func_ov002_02051eec
_L_0078:
    add     r0, r7, #0
_L_007a:
    bl      func_02024fd4
    pop     {r3, r4, r5, r6, r7, pc}
    dcd     data_ov082_020ba500
    dcd     0x00002bd0
    dcd     data_0204c240
    dcd     0x0000208c
    dcd     data_ov082_020ba45c
    dcd     0x00000f0d
    dcd     0x00000f0c
    dcd     0x00002c54
}
