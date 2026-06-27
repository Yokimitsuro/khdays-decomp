extern int *NNSi_FndAllocFromDefaultExpHeap(int);
extern void func_ov013_0207fa40(void);

asm void func_ov013_0207fba4(int a, int b, int c)
{
    push    {r4, r5, r6, lr}
    add     r5, r0, #0
    mov     r0, #0x1c
    add     r4, r1, #0
    add     r6, r2, #0
    bl      NNSi_FndAllocFromDefaultExpHeap
    strb    r5, [r0, #0x18]
    strb    r4, [r0, #0x19]
    str     r6, [r0, #0xc]
    mov     r1, #0
    str     r1, [r0, #0x14]
    ldr     r2, =func_ov013_0207fa40
    sub     r1, r1, #1
    cmp     r2, r1
    beq     _s1
    str     r2, [r0, #0]
_s1:
    mov     r2, #0
    sub     r1, r2, #1
    cmp     r2, r1
    beq     _s2
    str     r2, [r0, #4]
_s2:
    mov     r1, #0
    mvn     r1, r1
    cmp     r2, r1
    beq     _s3
    mov     r1, #0
    str     r1, [r0, #8]
_s3:
    pop     {r4, r5, r6, pc}
}
