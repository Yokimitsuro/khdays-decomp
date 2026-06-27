extern int data_02042418[];

asm void func_020110f4(int *dst)
{
    stmdb sp!, {r3, lr}
    mov r3, #0
    ldr ip, =data_02042418
    mov lr, r3
loop:
    ldr r1, [ip]
    add r3, r3, #1
    str r1, [r0, lr, lsl #2]
    ldr r2, [ip, #4]
    add r1, r0, lr, lsl #2
    str r2, [r1, #4]
    cmp r3, #5
    add ip, ip, #0x18
    add lr, lr, #2
    blt loop
    ldmia sp!, {r3, pc}
}
