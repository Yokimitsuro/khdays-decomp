/* NitroSDK original assembly (libraries/os/src/os_context.c). */

typedef int BOOL;
typedef unsigned int u32;
typedef struct OSContext OSContext;

#define HW_PSR_ARM_STATE             0x0
#define HW_PSR_SYS_MODE              0x1f
#define HW_PSR_THUMB_STATE           0x20
#define HW_SVC_STACK_SIZE            0x40
#define OS_CONTEXT_CPSR              0
#define OS_CONTEXT_LR                60
#define OS_CONTEXT_PC_PLUS4          64
#define OS_CONTEXT_R0                4
#define OS_CONTEXT_R1                8
#define OS_CONTEXT_R10               44
#define OS_CONTEXT_R11               48
#define OS_CONTEXT_R12               52
#define OS_CONTEXT_R2                12
#define OS_CONTEXT_R3                16
#define OS_CONTEXT_R4                20
#define OS_CONTEXT_R5                24
#define OS_CONTEXT_R6                28
#define OS_CONTEXT_R7                32
#define OS_CONTEXT_R8                36
#define OS_CONTEXT_R9                40
#define OS_CONTEXT_SP                56
#define OS_CONTEXT_SP_SVC            68

asm void OS_InitContext (register OSContext * context, register u32 newpc, register u32 newsp)
{
    add newpc, newpc, #4
    str newpc, [context, #OS_CONTEXT_PC_PLUS4]
    str newsp, [context, #OS_CONTEXT_SP_SVC]
    sub newsp, newsp, #HW_SVC_STACK_SIZE
    tst newsp, #4
    subne newsp, newsp, #4
    str newsp, [context, #OS_CONTEXT_SP]
    ands r1, newpc, #1
    movne r1, #HW_PSR_SYS_MODE | HW_PSR_THUMB_STATE
    moveq r1, #HW_PSR_SYS_MODE | HW_PSR_ARM_STATE
    str r1, [context, #OS_CONTEXT_CPSR]
    mov r1, #0
    str r1, [context, #OS_CONTEXT_R0]
    str r1, [context, #OS_CONTEXT_R1]
    str r1, [context, #OS_CONTEXT_R2]
    str r1, [context, #OS_CONTEXT_R3]
    str r1, [context, #OS_CONTEXT_R4]
    str r1, [context, #OS_CONTEXT_R5]
    str r1, [context, #OS_CONTEXT_R6]
    str r1, [context, #OS_CONTEXT_R7]
    str r1, [context, #OS_CONTEXT_R8]
    str r1, [context, #OS_CONTEXT_R9]
    str r1, [context, #OS_CONTEXT_R10]
    str r1, [context, #OS_CONTEXT_R11]
    str r1, [context, #OS_CONTEXT_R12]
    str r1, [context, #OS_CONTEXT_LR]
    bx lr
}
