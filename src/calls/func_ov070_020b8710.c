extern void func_ov022_020b15b0(void);
extern void func_ov022_020b14a4(void);
extern void func_ov022_020b1cec(void);
extern void *data_ov070_020b9c04;
extern void *data_ov070_020b9c14;
extern void *data_ov070_020b9c28;

asm void func_ov070_020b8710(void)
{
    stmfd   sp!, {r3, r4, r5, lr}
    mov     r5, r0
    add     r0, r5, #0x2f8
    add     r4, r0, #0x2000
    mov     r0, #0
    strb    r0, [r4, #0x334]
    ldrb    r0, [r5, #9]
    mov     r1, #3
    bl      func_ov022_020b15b0
    ldr     r2, [r5, #0x20]
    ldrb    r1, [r5, #9]
    add     r3, r2, #4
    ldr     r0, =data_ov070_020b9c04
    mov     r2, #0
    bl      func_ov022_020b14a4
    str     r0, [r4, #0x340]
    add     r0, r5, #0x2000
    ldr     r0, [r0, #0x644]
    ldrb    r1, [r5, #9]
    ldr     r2, [r0, #0x6c]
    ldr     r0, =data_ov070_020b9c14
    add     r3, r2, #0x28
    mov     r2, #1
    bl      func_ov022_020b14a4
    str     r0, [r4, #0x344]
    add     r3, r5, #0x2000
    ldr     r3, [r3, #0x644]
    ldrb    r1, [r5, #9]
    ldr     r3, [r3, #0xc]
    ldr     r0, =data_ov070_020b9c28
    mov     r2, #2
    add     r3, r3, #0x28
    bl      func_ov022_020b14a4
    str     r0, [r4, #0x348]
    add     r0, r5, #0xda0
    mov     r1, #0xcb
    bl      func_ov022_020b1cec
    ldrb    r0, [r4, #0x334]
    orr     r0, r0, #0xf
    strb    r0, [r4, #0x334]
    ldmfd   sp!, {r3, r4, r5, pc}
}
