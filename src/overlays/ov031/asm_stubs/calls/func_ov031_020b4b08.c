extern void VEC_Add(void);
extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void MTX_RotY33_(void);
extern void MTX_MultVec33(void);
extern void FX_Inv(void);
extern void func_01ffa724(void);
extern void VEC_MultAdd(void);
extern void func_02023c40(void);

asm void func_ov031_020b4b08(void)
{
    stmfd   sp!, {r4, r5, r6, lr}
    sub     sp, sp, #0x48
    mov     r6, r2
    ldr     r1, [r6, #4]
    ldr     r4, [r6, #0x138]
    add     r1, r1, r3
    str     r1, [r6, #4]
    add     r3, sp, #0x3c
    add     r1, r6, #0xcc
    mov     r5, r0
    ldmia   r1, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    mov     r0, r3
    mov     r2, r3
    add     r1, r6, #0x1c
    bl      VEC_Add
    add     r0, sp, #0x3c
    add     r2, sp, #0x24
    add     r1, r6, #0x10
    bl      VEC_Subtract
    add     r0, sp, #0x24
    mov     r1, r0
    bl      func_01ff8d18
    add     r0, sp, #0
    mov     r1, #0x1000
    mov     r2, #0
    bl      MTX_RotY33_
    add     r0, sp, #0x24
    add     r1, sp, #0
    add     r2, sp, #0x30
    bl      MTX_MultVec33
    ldr     ip, [r6, #4]
    cmp     ip, #0x6000
    movge   r6, #0x1000
    bge     _after
    ldr     r2, =0x55555556
    mov     r1, #0x6000
    smull   r0, r3, r2, ip
    add     r3, r3, ip, lsr #31
    add     r0, r3, r3, lsl #1
    bl      FX_Inv
    mov     r1, r0, asr #2
    add     r0, r0, r1, lsr #29
    mov     r0, r0, asr #3
    add     r6, r0, #0x1000
_after:
    add     r1, sp, #0x30
    mov     r0, r6
    mov     r2, r1
    bl      func_01ffa724
    add     r1, sp, #0x24
    add     r2, sp, #0x30
    mov     r3, r1
    rsb     r0, r6, #0x1000
    bl      VEC_MultAdd
    add     r0, sp, #0x24
    mov     r1, r0
    bl      func_01ff8d18
    bl      func_02023c40
    cmp     r0, #1
    ldr     r0, [r4, #0x10]
    bne     _skip
    add     r0, r0, r0, lsl #1
    add     r0, r0, r0, lsr #31
    mov     r0, r0, asr #1
_skip:
    add     r1, sp, #0x24
    mov     r2, r1
    bl      func_01ffa724
    add     r0, sp, #0x24
    ldmia   r0, {r0, r1, r2}
    stmia   r5, {r0, r1, r2}
    add     sp, sp, #0x48
    ldmfd   sp!, {r4, r5, r6, pc}
}
