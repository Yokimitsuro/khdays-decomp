extern int func_0201e470(int a, int b);
extern signed char data_027e0060;

asm void func_02001054(void)
{
    stmdb sp!, {r3, lr}
    ldr  r0, =data_027e0060
    ldrsb r0, [r0]
    cmp  r0, #0
    ldmneia sp!, {r3, pc}
    ldr  r1, =0x69
    mov  r0, #0
    bl   func_0201e470
    ldr  r0, =data_027e0060
    mov  r1, #1
    strb r1, [r0]
    ldmia sp!, {r3, pc}
}
