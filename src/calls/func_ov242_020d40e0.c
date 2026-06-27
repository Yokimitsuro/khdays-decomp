extern void func_0203c634(void);
extern void func_ov242_020d439c(void);
extern void func_ov242_020d4154(void);
extern void func_ov242_020d432c(void);

asm void func_ov242_020d40e0(void)
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
    ldr     r2, =func_ov242_020d439c
    add     r3, r1, #0xb0
    mov     r1, #1
    str     r3, [ip, #0xc]
    bl      func_0203c634
    ldr     r2, =func_ov242_020d4154
    mov     r0, r4
    mov     r1, #0
    bl      func_0203c634
    ldr     r2, =func_ov242_020d432c
    mov     r0, r4
    mov     r1, #2
    bl      func_0203c634
    ldmfd   sp!, {r4, pc}
}
