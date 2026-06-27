extern char data_0204430c[];

asm void func_02001a34(void *node)
{
    stmdb sp!, {r3, lr}
    ldr r1, =data_0204430c
    mov ip, #0
    ldr lr, [r1, #0x2c]
    mov r3, lr
    b check
walk:
    mov ip, r3
    ldr r3, [r3, #0x68]
check:
    cmp r3, #0
    beq insert
    ldr r2, [r3, #0x70]
    ldr r1, [r0, #0x70]
    cmp r2, r1
    blo walk
insert:
    cmp ip, #0
    ldrne r1, [ip, #0x68]
    strne r1, [r0, #0x68]
    strne r0, [ip, #0x68]
    ldmneia sp!, {r3, pc}
    ldr r1, =data_0204430c
    str lr, [r0, #0x68]
    str r0, [r1, #0x2c]
    ldmia sp!, {r3, pc}
}
