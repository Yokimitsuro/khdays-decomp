extern int func_0201e470(int, int);
extern char data_ov029_020b30b0[];
extern char data_ov029_020b320c[];
extern char data_ov029_020b3200[];
extern char data_ov029_020b2f70[];

asm void func_ov029_020b2ee0(int a, int b)
{
    push    {r3, r4, r5, r6, r7, lr}
    ldr     r2, =data_ov029_020b30b0
    lsl     r1, r1, #4
    mov     r5, #0
    mvn     r5, r5
    add     r7, r2, r1
    str     r1, [sp]
    add     r1, r7, #0
    ldr     r0, =data_ov029_020b320c
    mov     r4, #3
    add     r1, #0xc
    add     r2, r5, #0
    add     r3, r5, #0
_lp:
    ldr     r6, [r0, #0]
    cmp     r6, r3
    bne     _next
    ldr     r6, [r1, #0]
    cmp     r6, r2
    beq     _next
    lsl     r1, r4, #2
    ldr     r5, [r7, r1]
    ldr     r0, =data_ov029_020b3200
    str     r5, [r0, r1]
    b       _go
_next:
    sub     r0, r0, #4
    sub     r1, r1, #4
    sub     r4, r4, #1
    bpl     _lp
_go:
    mov     r0, #0
    add     r1, r5, #0
    bl      func_0201e470
    ldr     r2, =data_ov029_020b2f70
    ldr     r0, [sp]
    lsl     r1, r4, #2
    add     r0, r2, r0
    ldr     r0, [r1, r0]
    blx     r0
    add     r0, r5, #0
    pop     {r3, r4, r5, r6, r7, pc}
}
