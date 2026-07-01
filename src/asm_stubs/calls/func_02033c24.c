extern void func_0201a124(void *base, int a, int b);
extern int data_0204c234;

asm void func_02033c24(int a, int b)
{
    stmdb sp!, {r4, lr}
    ldr r2, =data_0204c234
    ldr r3, =0x000b44c4
    ldr ip, [r2]
    mov r4, r0
    mov r2, r1
    mov r1, r4
    add r0, ip, r3
    bl func_0201a124
    ldr r0, =data_0204c234
    ldr r0, [r0]
    add r0, r0, #0xb4000
    strb r4, [r0, #0x6fd]
    ldmia sp!, {r4, pc}
}
