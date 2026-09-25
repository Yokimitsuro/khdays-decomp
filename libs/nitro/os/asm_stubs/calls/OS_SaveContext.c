/* NitroSDK original assembly (libraries/os/src/os_context.c). */

typedef int BOOL;
typedef unsigned int u32;
typedef struct OSContext OSContext;
extern void CP_SaveContext(void);

#define HW_PSR_ARM_STATE             0x0
#define HW_PSR_FIQ_DISABLE           0x40
#define HW_PSR_IRQ_DISABLE           0x80
#define HW_PSR_SVC_MODE              0x13
#define OS_CONTEXT_CPSR              0
#define OS_CONTEXT_CP_CONTEXT        72
#define OS_CONTEXT_PC_PLUS4          64
#define OS_CONTEXT_R0                4
#define OS_CONTEXT_SP_SVC            68

asm BOOL OS_SaveContext (register OSContext * context)
{
    stmfd sp !, { lr, r0 }
    add r0, r0, #OS_CONTEXT_CP_CONTEXT
    ldr r1, = CP_SaveContext
    blx r1
    ldmfd sp !, { lr, r0 }
    add r1, r0, #OS_CONTEXT_CPSR
    mrs r2, cpsr
    str r2, [r1], #OS_CONTEXT_R0 - OS_CONTEXT_CPSR
    mov r0, #HW_PSR_SVC_MODE | HW_PSR_IRQ_DISABLE | HW_PSR_FIQ_DISABLE | HW_PSR_ARM_STATE
    msr cpsr_c, r0
    str sp, [r1, #OS_CONTEXT_SP_SVC - OS_CONTEXT_R0]
    msr cpsr_c, r2
    mov r0, #1
    stmia r1, {r0 - r14}
    add r0, pc, #8
    str r0, [r1, #OS_CONTEXT_PC_PLUS4 - OS_CONTEXT_R0]
    mov r0, #0
    bx lr
}
