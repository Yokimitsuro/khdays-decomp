extern void OS_EnableProtectionUnit(void);
extern int data_020445b4[];
extern int data_020445b8;
extern int data_020445bc;
extern int data_020445e0;

asm void func_0200302c(void)
{
    stmdb sp!, {r3, lr}
    ldr r0, =data_020445b4
    ldr r0, [r0, #8]
    cmp r0, #0
    ldmeqia sp!, {r3, pc}
    mrs r2, cpsr
    mov r0, sp
    ldr r1, =0x9f
    msr cpsr_fsxc, r1
    mov r1, sp
    mov sp, r0
    stmdb sp!, {r1, r2}
    bl OS_EnableProtectionUnit
    ldr r0, =data_020445e0
    ldr r1, =data_020445b8
    ldr r1, [r1]
    ldr ip, =data_020445bc
    ldr ip, [ip]
    ldr lr, =0x0200307c
    bx ip
    DCD 0xebffff7b
    ldmia sp!, {r1, r2}
    mov sp, r1
    msr cpsr_fsxc, r2
    ldmia sp!, {r3, pc}
}
