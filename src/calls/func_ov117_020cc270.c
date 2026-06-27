extern void func_0203be68(void);
extern void func_0203be9c(void);
extern void func_0203babc(void);
extern void func_0203b9fc(void);
extern void func_ov117_020cc1c8(void);
extern void func_0203c7ac(void);

asm void func_ov117_020cc270(void *r0)
{
    stmfd   sp!, {r4, r5, r6, lr}
    mov     r6, r1
    mov     r4, r0
    mov     r5, r2
    cmp     r6, #3
    bne     _other
    mov     r1, #0
    ldr     r0, [r4, #0x384]
    mov     r2, r1
    bl      func_0203be68
    mov     r2, r0
    ldr     r0, [r4, #0x384]
    mov     r1, #0
    bl      func_0203be9c
    mov     r1, #0
    ldr     r0, [r4, #0x384]
    mov     r2, r1
    mov     r3, r5
    bl      func_0203babc
    ldr     r0, [r4, #0x384]
    mov     r1, #3
    mov     r2, #0
    bl      func_0203be68
    mov     r2, r0
    ldr     r0, [r4, #0x384]
    mov     r1, #3
    bl      func_0203be9c
    mov     r3, r5
    ldr     r0, [r4, #0x384]
    mov     r1, #3
    mov     r2, #0
    bl      func_0203babc
    b       _check
_other:
    mov     r1, r6, lsl #0x10
    ldr     r0, [r4, #0x384]
    mov     r3, r5
    mov     r2, r1, asr #0x10
    mov     r1, #0
    bl      func_0203b9fc
    mov     r1, r6, lsl #0x10
    ldr     r0, [r4, #0x384]
    mov     r3, r5
    mov     r2, r1, asr #0x10
    mov     r1, #3
    bl      func_0203b9fc
_check:
    ldr     r0, [r4, #0x390]
    cmp     r0, #0
    addne   r0, r4, #0x100
    ldrnesb r0, [r0, #0xc6]
    cmpne   r0, #7
    beq     _end
    mov     r0, r4
    bl      func_ov117_020cc1c8
_end:
    ldr     r0, [r4, #0x384]
    mov     r1, #0
    bl      func_0203c7ac
    ldmfd   sp!, {r4, r5, r6, pc}
}
