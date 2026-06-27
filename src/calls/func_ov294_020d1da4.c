extern int func_0203c634(void *r0, int r1, void *r2);
extern void func_ov294_020d1f54(void *p);
extern void func_ov294_020d1e44(void *p);
extern void func_ov294_020d1f50(void *p);

asm void func_ov294_020d1da4(void *r0)
{
    stmfd   sp!, {r4, lr}
    mov     r4, r0
    ldr     r3, [r4, #4]
    mov     r2, #0
    ldr     r1, [r3]
    sub     ip, r2, #1
    strb    r2, [r1, #0x1c6]
    ldr     r1, [r3]
    ldr     r2, =func_ov294_020d1f54
    strb    ip, [r1, #0x1c7]
    ldr     ip, [r3]
    mov     r1, #1
    add     ip, ip, #0xb0
    str     ip, [r3, #4]
    ldr     ip, [r3]
    ldr     ip, [ip, #0x384]
    add     ip, ip, #0xad
    str     ip, [r3, #8]
    ldr     lr, [r3]
    ldrh    ip, [lr, #0x60]
    mov     r3, ip, lsl #0x10
    mov     r3, r3, lsr #0x18
    orr     r3, r3, #0x1e
    bic     ip, ip, #0xff00
    mov     r3, r3, lsl #0x18
    orr     r3, ip, r3, lsr #0x10
    strh    r3, [lr, #0x60]
    bl      func_0203c634
    ldr     r2, =func_ov294_020d1e44
    mov     r0, r4
    mov     r1, #0
    bl      func_0203c634
    ldr     r2, =func_ov294_020d1f50
    mov     r0, r4
    mov     r1, #2
    bl      func_0203c634
    ldmfd   sp!, {r4, pc}
}
