extern void func_0202926c(void *p);
extern int data_02042910;

asm void func_0202930c(void *a, int b, int c, int d, int e)
{
    stmdb sp!, {r3, r4, r5, lr}
    mov r5, r0
    mov r4, r3
    bl func_0202926c
    mov r1, #2
    ldr r0, =data_02042910
    strb r1, [r5, #0x21]
    str r0, [r5, #0x1c]
    ldr r0, [sp, #0x10]
    str r4, [r5, #0x38]
    str r0, [r5, #0x3c]
    mov r0, #1
    ldmia sp!, {r3, r4, r5, pc}
}
