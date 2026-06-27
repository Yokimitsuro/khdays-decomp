extern unsigned int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(unsigned int);
extern volatile unsigned int data_02044664;

asm void func_02003284(unsigned int a, unsigned int b)
{
    stmdb sp!, {r4, r5, r6, lr}
    mov r5, r0
    mov r4, r1
    bl OS_DisableInterrupts
    mov r3, r5, lsr #0x10
    mov ip, #0x1
    rsb r1, ip, #0x10000
    ldr lr, =0x04000214
    mov r6, #0x8
    ldr r2, =data_02044664
    str r6, [lr]
    str ip, [r2, #0x4]
    orr r3, r3, r4, lsl #0x10
    str r3, [r2, #0x8]
    mov r4, r4, lsr #0x10
    ldr r3, =0x04000102
    str r4, [r2, #0xc]
    mov r2, #0x0
    strh r2, [r3]
    and r1, r5, r1
    strh r1, [r3, #-0x2]
    mov r1, #0xc1
    strh r1, [r3]
    bl OS_RestoreInterrupts
    ldmia sp!, {r4, r5, r6, pc}
}
