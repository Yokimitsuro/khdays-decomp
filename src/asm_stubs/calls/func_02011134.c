extern int data_02042418[];

asm void func_02011134(int *src)
{
    stmdb sp!, {r3, lr}
    mov r3, #0
    ldr lr, =data_02042418
    mov ip, r3
loop:
    ldr r2, [r0, ip, lsl #2]
    add r1, r0, ip, lsl #2
    str r2, [lr]
    ldr r1, [r1, #4]
    add r3, r3, #1
    str r1, [lr, #4]
    cmp r3, #5
    add ip, ip, #2
    add lr, lr, #0x18
    blt loop
    ldmia sp!, {r3, pc}
}
