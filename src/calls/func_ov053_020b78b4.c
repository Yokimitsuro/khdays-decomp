extern void func_0202a634(void *a, int b, int c, int d);
extern void func_0202accc(void *a, int b, int c, int d);
extern int data_ov053_020b7e60;
extern int data_ov053_020b7e34;

asm void func_ov053_020b78b4(void)
{
    push    {r4, lr}
    ldr     r0, =data_ov053_020b7e60
    ldr     r1, =data_ov053_020b7e34
    ldr     r3, [r0, #0]
    ldr     r0, =0x2ce4
    mov     r2, #1
    add     r4, r3, r0
    mov     r0, #0
    str     r0, [r4, #0x24]
    str     r0, [r4, #0]
    str     r0, [r4, #0x10]
    str     r0, [r4, #0xc]
    ldrb    r3, [r3, #9]
    add     r0, r4, #0
    add     r0, #0x28
    add     r3, r3, #7
    bl      func_0202a634
    mov     r2, #0x42
    add     r0, r4, #0
    mov     r1, #0
    lsl     r2, r2, #2
    add     r0, #0x28
    add     r2, r4, r2
    add     r3, r1, #0
    bl      func_0202accc
    mov     r2, #0x42
    add     r0, r4, #0
    lsl     r2, r2, #2
    add     r0, #0x28
    mov     r1, #2
    add     r2, r4, r2
    mov     r3, #0
    bl      func_0202accc
    pop     {r4, pc}
}
