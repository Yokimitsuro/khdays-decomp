extern int func_0203c634(void *r0, int r1, int r2);
extern void func_ov301_020cc63c(void *p);
extern void func_ov301_020cc6f8(void *p);
extern void func_ov301_020cc6fc(void *p);

asm void func_ov301_020cc338(void *r0)
{
    stmfd   sp!, {r4, lr}
    ldr     r4, [r0, #4]
    mvn     r2, #0
    ldr     r3, [r4]
    add     r1, r3, #0x100
    ldrsb   r1, [r1, #0xc7]
    cmp     r1, r2
    beq     _end
    strb    r1, [r3, #0x1c6]
    ldr     r3, [r4]
    ldrh    r2, [r3, #0x60]
    mov     r1, r2, lsl #0x10
    mov     r1, r1, lsr #0x18
    bic     r1, r1, #0xc6
    mov     r1, r1, lsl #0x10
    mov     r1, r1, lsr #0x10
    bic     r2, r2, #0xff00
    mov     r1, r1, lsl #0x18
    orr     r1, r2, r1, lsr #0x10
    strh    r1, [r3, #0x60]
    ldr     r1, [r4]
    add     r1, r1, #0x100
    ldrh    r2, [r1, #0xae]
    bic     r2, r2, #3
    strh    r2, [r1, #0xae]
    ldr     r1, [r4]
    ldr     r3, [r1, #0x388]
    ldr     r2, [r3, #8]
    mov     r1, r2, lsl #0x18
    mov     r1, r1, lsr #0x18
    orr     r1, r1, #1
    bic     r2, r2, #0xff
    and     r1, r1, #0xff
    orr     r1, r2, r1
    str     r1, [r3, #8]
    ldr     r3, [r4]
    ldrh    r2, [r3, #0x60]
    mov     r1, r2, lsl #0x10
    mov     r1, r1, lsr #0x18
    orr     r1, r1, #0x40
    bic     r2, r2, #0xff00
    mov     r1, r1, lsl #0x18
    orr     r1, r2, r1, lsr #0x10
    strh    r1, [r3, #0x60]
    ldr     r1, [r4]
    add     r1, r1, #0x100
    ldrsb   r1, [r1, #0xc6]
    cmp     r1, #0
    beq     _c0
    cmp     r1, #2
    beq     _c2
    cmp     r1, #3
    beq     _c3
    b       _end
_c0:
    ldr     r2, =func_ov301_020cc63c
    mov     r1, #1
    bl      func_0203c634
    b       _end
_c2:
    ldr     r2, =func_ov301_020cc6f8
    mov     r1, #1
    bl      func_0203c634
    b       _end
_c3:
    ldr     r2, =func_ov301_020cc6fc
    mov     r1, #1
    bl      func_0203c634
_end:
    ldr     r0, [r4]
    mvn     r1, #0
    strb    r1, [r0, #0x1c7]
    ldmfd   sp!, {r4, pc}
}
