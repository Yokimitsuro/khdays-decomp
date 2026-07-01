extern void func_0202926c(void *p, int a1, int a2, int a3);
extern char data_02042940[];

asm void func_020292a4(void *p, int arg1, int arg2, int arg3, int arg4)
{
    stmdb sp!, {r3, r4, r5, lr}
    mov  r5, r0
    mov  r4, r3
    bl   func_0202926c
    mov  r0, #1
    ldr  r1, =data_02042940
    strb r0, [r5, #0x21]
    str  r1, [r5, #0x1c]
    ldr  r1, [sp, #0x10]
    str  r4, [r5, #0x38]
    str  r1, [r5, #0x3c]
    ldmia sp!, {r3, r4, r5, pc}
}
