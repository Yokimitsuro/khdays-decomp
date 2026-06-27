extern void func_0203c634(void *r0, int r1, void *r2);
extern void func_ov241_020d075c(void);
extern void func_ov241_020d0514(void);
extern void func_ov241_020d06ec(void);

asm void func_ov241_020d04a0(void *r0)
{
    stmfd   sp!, {r4, lr}
    mov     r4, r0
    ldr     ip, [r4, #4]
    mov     r3, #0
    ldr     r1, [ip]
    sub     r2, r3, #1
    strb    r3, [r1, #0x1c6]
    ldr     r1, [ip]
    strb    r2, [r1, #0x1c7]
    str     r3, [ip, #4]
    str     r3, [ip, #8]
    ldr     r1, [ip]
    ldr     r2, =func_ov241_020d075c
    add     r3, r1, #0xb0
    mov     r1, #1
    str     r3, [ip, #0xc]
    bl      func_0203c634
    ldr     r2, =func_ov241_020d0514
    mov     r0, r4
    mov     r1, #0
    bl      func_0203c634
    ldr     r2, =func_ov241_020d06ec
    mov     r0, r4
    mov     r1, #2
    bl      func_0203c634
    ldmfd   sp!, {r4, pc}
}
