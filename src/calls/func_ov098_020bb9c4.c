extern void func_01ff8d18(void *r0, void *r1);
extern int VEC_Mag(void *r0);
extern void func_01ffa724(int r0, void *r1, void *r2);
extern void VEC_Add(void *r0, void *r1, void *r2);
extern void func_ov098_020bba88(void *r0, void *r1);
extern char data_ov098_020bbda0[];

asm void func_ov098_020bb9c4(void *r0, void *r1)
{
    stmfd   sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
    sub     sp, sp, #0x18
    ldr     r2, [pc, #0xb0]
    mov     r6, r1
    ldr     r2, [r2]
    add     r3, sp, #0xc
    add     r1, r2, #0x2c
    add     r4, r1, #0x2c00
    ldr     r5, [r4, #0x10]
    mov     r7, r0
    ldmia   r6, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    mov     r0, r3
    mov     r1, r3
    bl      func_01ff8d18
    mov     r0, r6
    bl      VEC_Mag
    ldr     r1, [r4, #0x10]
    add     r0, r1, r0
    cmp     r0, #0x2000
    addle   sp, sp, #0x18
    str     r0, [r4, #0x10]
    ldmlefd sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
    add     r9, sp, #0xc
    add     r8, sp, #0
_L_loop:
    ldmia   r6, {r0, r1, r2}
    stmia   r9, {r0, r1, r2}
    mov     r0, r9
    mov     r1, r9
    bl      func_01ff8d18
    mov     r1, r9
    mov     r2, r9
    rsb     r0, r5, #0x2000
    bl      func_01ffa724
    mov     r0, r7
    mov     r1, r9
    mov     r2, r8
    bl      VEC_Add
    mov     r0, r8
    mov     r1, r9
    bl      func_ov098_020bba88
    ldr     r0, [r4, #0x10]
    sub     r5, r0, #0x2000
    str     r5, [r4, #0x10]
    cmp     r5, #0x2000
    bgt     _L_loop
    add     sp, sp, #0x18
    ldmfd   sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
    dcd     data_ov098_020bbda0
}
