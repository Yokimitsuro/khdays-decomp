extern void func_02016294(void);
extern void func_0202ea48(void);
extern void func_0203c960(void);
extern void func_0203ca30(void);
extern void func_0202f384(void);
extern void func_020050b4(void);
extern void func_0202f188(void);
extern void func_0203c9d0(void);
extern void data_02042258(void);
extern void data_02042264(void);

asm void func_ov241_020cfc04(void *r0)
{
    stmfd   sp!, {r3, r4, lr}
    sub     sp, sp, #0x7c
    ldr     r2, [r0, #4]
    ldr     r1, [r0, #8]
    ldr     r4, [r2, #0x2c]
    tst     r1, #0x10
    ldrneb  r0, [r0, #0xae]
    add     r1, r4, #0x300
    ldrh    r2, [r1, #0xac]
    mvneq   r0, #0
    mov     r0, r0, lsl #0x10
    mov     r3, r0, lsr #0x10
    cmp     r2, r0, lsr #0x10
    bne     _l10c
    add     r0, sp, #0x4c
    add     r1, sp, #0x28
    bl      func_02016294
    add     r0, sp, #0x18
    add     r1, sp, #0x28
    bl      func_0202ea48
    add     r0, sp, #0x70
    add     r3, sp, #0xc
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    ldr     r1, [r4, #0x9c]
    ldr     r0, [r1, #0x44]
    add     r0, r0, #0x400
    str     r0, [r1, #0x44]
    ldr     r0, [r4, #0x9c]
    ldr     r0, [r0, #0x44]
    str     r0, [sp, #0x10]
    ldr     r0, [r4, #0x38c]
    add     r0, r0, #0x30
    bl      func_0203c960
    ldr     r0, [r4, #0x38c]
    add     r1, sp, #0x70
    add     r0, r0, #0x30
    bl      func_0203ca30
    ldr     r2, =data_02042258
    add     r0, sp, #0
    add     r1, sp, #0x18
    bl      func_0202f384
    ldr     r0, [sp]
    ldr     r1, [sp, #8]
    bl      func_020050b4
    str     r0, [r4, #0x3bc]
    ldr     r1, =data_02042264
    ldr     r2, [r4, #0x3bc]
    add     r0, sp, #0x18
    bl      func_0202f188
    ldr     r0, [r4, #0xb0]
    str     r0, [sp, #0xc]
    ldr     r0, [r4, #0xb8]
    str     r0, [sp, #0x14]
    ldr     r0, [r4, #0x3a0]
    add     r0, r0, #0x30
    bl      func_0203c960
    ldr     r0, [r4, #0x3a0]
    add     r1, sp, #0x18
    add     r0, r0, #0x30
    bl      func_0203c9d0
    ldr     r0, [r4, #0x3a0]
    add     r1, sp, #0xc
    add     r0, r0, #0x30
    bl      func_0203ca30
    add     sp, sp, #0x7c
    ldmfd   sp!, {r3, r4, pc}
_l10c:
    ldrh    r0, [r1, #0xae]
    cmp     r3, r0
    bne     _l148
    add     r0, sp, #0x4c
    add     r1, sp, #0x28
    bl      func_02016294
    ldr     r0, [r4, #0x390]
    add     r0, r0, #0x30
    bl      func_0203c960
    ldr     r0, [r4, #0x390]
    add     r1, sp, #0x70
    add     r0, r0, #0x30
    bl      func_0203ca30
    add     sp, sp, #0x7c
    ldmfd   sp!, {r3, r4, pc}
_l148:
    ldrh    r0, [r1, #0xb0]
    cmp     r3, r0
    addne   sp, sp, #0x7c
    ldmnefd sp!, {r3, r4, pc}
    add     r0, sp, #0x4c
    add     r1, sp, #0x28
    bl      func_02016294
    ldr     r0, [r4, #0x394]
    add     r0, r0, #0x30
    bl      func_0203c960
    ldr     r0, [r4, #0x394]
    add     r1, sp, #0x70
    add     r0, r0, #0x30
    bl      func_0203ca30
    add     sp, sp, #0x7c
    ldmfd   sp!, {r3, r4, pc}
}
