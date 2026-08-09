extern char data_027e006c[];
extern char data_02044330[];
extern void CP_SaveContext(void *context);
extern void CPi_RestoreContext(void *context);

/* NitroSDK IRQ callback continuation and optional thread-context switch. */
asm void func_01ff81a0(void)
{
    ldr     ip, =data_027e006c
    mov     r3, #0
    ldr     ip, [ip]
    mov     r2, #1
    cmp     ip, #0
    beq     checkThreadSwitch
clearIrqThreadState:
    str     r2, [ip, #0x64]
    str     r3, [ip, #0x78]
    str     r3, [ip, #0x7c]
    ldr     r0, [ip, #0x80]
    str     r3, [ip, #0x80]
    mov     ip, r0
    cmp     ip, #0
    bne     clearIrqThreadState
    ldr     ip, =data_027e006c
    str     r3, [ip]
    str     r3, [ip, #4]
    ldr     ip, =data_02044330
    mov     r1, #1
    strh    r1, [ip]
checkThreadSwitch:
    ldr     ip, =data_02044330
    ldrh    r1, [ip]
    cmp     r1, #0
    ldreq   pc, [sp], #4
    mov     r1, #0
    strh    r1, [ip]
    mov     r3, #0xd2
    msr     cpsr_c, r3
    add     r2, ip, #8
    ldr     r1, [r2]
scanRunnableThreads:
    cmp     r1, #0
    ldrneh  r0, [r1, #0x64]
    cmpne   r0, #1
    ldrne   r1, [r1, #0x68]
    bne     scanRunnableThreads
    cmp     r1, #0
    bne     compareCurrentThread
returnFromIrq:
    mov     r3, #0x92
    msr     cpsr_c, r3
    ldr     pc, [sp], #4
compareCurrentThread:
    ldr     r0, [ip, #4]
    cmp     r1, r0
    beq     returnFromIrq
    ldr     r3, [ip, #0xc]
    cmp     r3, #0
    beq     saveThreadContext
    stmdb   sp!, {r0, r1, ip}
    mov     lr, pc
    bx      r3
    ldmia   sp!, {r0, r1, ip}
saveThreadContext:
    str     r1, [ip, #4]
    mrs     r2, spsr
    str     r2, [r0, #0]!
    stmdb   sp!, {r0, r1}
    add     r0, r0, #0
    add     r0, r0, #0x48
    ldr     r1, =CP_SaveContext
    blx     r1
    ldmia   sp!, {r0, r1}
    ldmib   sp!, {r2, r3}
    stmib   r0!, {r2, r3}
    ldmib   sp!, {r2, r3, ip, lr}
    stmib   r0!, {r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, ip, sp, lr}^
    stmib   r0!, {lr}
    mov     r3, #0xd3
    msr     cpsr_c, r3
    stmib   r0!, {sp}
    stmdb   sp!, {r1}
    add     r0, r1, #0
    add     r0, r0, #0x48
    ldr     r1, =CPi_RestoreContext
    blx     r1
    ldmia   sp!, {r1}
    ldr     sp, [r1, #0x44]
    mov     r3, #0xd2
    msr     cpsr_c, r3
    ldr     r2, [r1, #0]!
    msr     spsr_fc, r2
    ldr     lr, [r1, #0x40]
    ldmib   r1, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, ip, sp, lr}^
    mov     r0, r0
    stmda   sp!, {r0, r1, r2, r3, ip, lr}
    ldmia   sp!, {pc}
}
