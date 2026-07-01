extern void *func_0203d15c(void *p);

asm void func_01fffca8(void *a, void *b, int c)
{
    stmdb sp!, {r3, r4, r5, r6, r7, lr}
    mov r4, r0
    ldr r6, [r4, #4]
    mov r7, r2
    ldr r0, [r6, #8]
    cmp r0, r7
    bhi found
loop:
    ldr r6, [r6, #4]
    ldr r0, [r6, #8]
    cmp r0, r7
    bls loop
found:
    ldr r5, [r6]
    add r0, r1, #0x10
    bl func_0203d15c
    stmia r0, {r5, r6}
    str r0, [r5, #4]
    str r0, [r6]
    str r7, [r0, #8]
    add r1, r0, #0x10
    str r1, [r0, #0xc]
    ldr r1, [r4, #0x20]
    add r1, r1, #1
    str r1, [r4, #0x20]
    ldr r0, [r0, #0xc]
    ldmia sp!, {r3, r4, r5, r6, r7, pc}
}
