/* NitroSDK original assembly (libraries/os/src/os_exception.c). */

typedef int BOOL;
typedef unsigned int u32;

typedef struct OSContext {
    u32 cpsr;
    u32 r[13];
    u32 sp;
    u32 lr;
    u32 pc_plus4;
    u32 sp_svc;
    char cp_context[0x1c];
} OSContext;

typedef struct OSiExContext {
    OSContext context;
    u32 cp15;
    u32 spsr;
    u32 exinfo;
    u32 debug[4];
} OSiExContext;

extern OSiExContext data_020445e0;         /* OSi_ExContext (.bss) */

#define OS_CONTEXT_CPSR              0
#define OS_CONTEXT_PC_PLUS4          64
#define OS_CONTEXT_R0                4
#define OS_CONTEXT_R1                8
#define OS_CONTEXT_R12               52
#define OS_CONTEXT_R13               56
#define OS_CONTEXT_R14               60
#define OS_CONTEXT_R2                12
#define OS_CONTEXT_R3                16
#define OS_CONTEXT_R4                20
#define OSi_ExContext                data_020445e0

asm void OSi_SetExContext (void)
{
    ldr r1, = OSi_ExContext;
    mrs r2, CPSR
    str r2, [r1, #OSiExContext.debug[1]]
    str r0, [r1, #OSiExContext.exinfo]
    ldr r0, [r12, #0]
    str r0, [r1, #OS_CONTEXT_R0]
    ldr r0, [r12, #4]
    str r0, [r1, #OS_CONTEXT_R1]
    ldr r0, [r12, #8]
    str r0, [r1, #OS_CONTEXT_R2]
    ldr r0, [r12, #12]
    str r0, [r1, #OS_CONTEXT_R3]
    ldr r2, [r12, #16]
    bic r2, r2, #1
    add r0, r1, #OS_CONTEXT_R4
    stmia r0, {r4 - r11}
    str r12, [r1, #OSiExContext.debug[0]]
    ldr r0, [r2, #0]
    str r0, [r1, #OSiExContext.cp15]
    ldr r3, [r2, #4]
    str r3, [r1, #OS_CONTEXT_CPSR]
    ldr r0, [r2, #8]
    str r0, [r1, #OS_CONTEXT_R12]
    ldr r0, [r2, #12]
    str r0, [r1, #OS_CONTEXT_PC_PLUS4]
    mrs r0, CPSR
    orr r3, r3, #0x80
    bic r3, r3, #0x20
    msr CPSR_cxsf, r3
    str sp, [r1, #OS_CONTEXT_R13]
    str lr, [r1, #OS_CONTEXT_R14]
    mrs r2, SPSR
    str r2, [r1, #OSiExContext.debug[3]]
    msr CPSR_cxsf, r0
    bx lr
}
