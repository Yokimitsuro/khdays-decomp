typedef unsigned int u32;
typedef unsigned short u16;

extern u32 OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(u32);

asm int func_020093e8(u32 a, u32 b, u32 c, u32 d)
{
    stmdb sp!, {r3, lr}
    ldr ip, [sp]
    ldr r3, =0x04000184
    bic ip, ip, #0x1f
    and r0, r0, #0x1f
    orr ip, ip, r0
    ldrh r0, [r3]
    bic ip, ip, #0x20
    mov r2, r2, lsl #0x1f
    orr r2, ip, r2, lsr #26
    and r2, r2, #0x3f
    orr r1, r2, r1, lsl #6
    str r1, [sp]
    tst r0, #0x4000
    beq _disable
    ldrh r1, [r3]
    mvn r0, #0
    orr r1, r1, #0xc000
    strh r1, [r3]
    ldmia sp!, {r3, pc}
_disable:
    bl OS_DisableInterrupts
    ldr r2, =0x04000184
    ldrh r1, [r2]
    tst r1, #2
    beq _send
    bl OS_RestoreInterrupts
    mvn r0, #1
    ldmia sp!, {r3, pc}
_send:
    ldr r1, [sp]
    str r1, [r2, #4]
    bl OS_RestoreInterrupts
    mov r0, #0
    ldmia sp!, {r3, pc}
}
