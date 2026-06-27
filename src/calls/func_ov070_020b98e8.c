extern void MTX_RotY33_(void);
extern void MTX_MultVec33(void);
extern void VEC_Mag(void);
extern void func_01ff8d18(void);
extern void func_ov022_02091324(void);
extern int data_ov070_020b9ca0;
extern int data_0203d210;

asm void func_ov070_020b98e8(void)
{
    stmfd   sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub     sp, sp, #0x5c
    add     r11, sp, #0x30
    mov     r10, r1
    ldmia   r0, {r0, r1, r2}
    stmia   r11, {r0, r1, r2}
    mov     r9, #0
    ldr     r3, =data_ov070_020b9ca0
    mov     r2, #2
    mov     r1, #7
    mov     r0, #0x1c00
    ldr     r7, [r3]
    ldr     r4, =data_0203d210
    mov     r8, r9
    str     r2, [sp, #0x44]
    str     r9, [sp, #0x4c]
    str     r9, [sp, #0x50]
    str     r1, [sp, #0x48]
    str     r9, [sp, #0x54]
    str     r9, [sp, #0x58]
    strh    r0, [sp, #0x42]
    add     r6, sp, #0
    add     r5, sp, #0xc
_loop:
    mov     r0, r9, asr #4
    mov     ip, r0, lsl #1
    mov     r3, ip, lsl #1
    ldmia   r10, {r0, r1, r2}
    stmia   r6, {r0, r1, r2}
    add     r0, r4, ip, lsl #1
    ldrsh   r1, [r4, r3]
    ldrsh   r2, [r0, #2]
    mov     r0, r5
    bl      MTX_RotY33_
    mov     r0, r6
    mov     r1, r5
    mov     r2, r6
    bl      MTX_MultVec33
    mov     r0, r6
    bl      VEC_Mag
    cmp     r0, #0
    beq     _skip
    mov     r0, r6
    mov     r1, r6
    bl      func_01ff8d18
_skip:
    ldr     ip, [sp]
    ldr     r3, [sp, #4]
    ldr     r2, [sp, #8]
    mov     r0, r7
    mov     r1, r11
    strh    ip, [sp, #0x3c]
    strh    r3, [sp, #0x3e]
    strh    r2, [sp, #0x40]
    bl      func_ov022_02091324
    add     r0, r9, #0x55
    add     r0, r0, #0x5500
    mov     r0, r0, lsl #0x10
    add     r8, r8, #1
    cmp     r8, #3
    mov     r9, r0, lsr #0x10
    blt     _loop
    add     sp, sp, #0x5c
    ldmfd   sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
