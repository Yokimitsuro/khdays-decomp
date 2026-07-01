extern void func_02029250(void *p);
extern void func_0202922c(void *a, void *b);

asm void func_020293c4(void *a, void *b)
{
    stmdb sp!, {r3, r4, r5, lr}
    mov r4, r1
    ldrb r2, [r4, #0x20]
    mov r5, r0
    tst r2, #1
    ldmeqia sp!, {r3, r4, r5, pc}
    bl func_02029250
    mov r0, r5
    mov r1, r4
    bl func_0202922c
    ldrb r0, [r4, #0x20]
    bic r0, r0, #1
    strb r0, [r4, #0x20]
    ldmia sp!, {r3, r4, r5, pc}
}
