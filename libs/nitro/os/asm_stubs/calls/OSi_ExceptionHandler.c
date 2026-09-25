/* NitroSDK original assembly (libraries/os/src/os_exception.c). */

typedef int BOOL;
typedef unsigned int u32;
extern void OSi_GetAndDisplayContext(void);
extern void *data_020445b4;             /* OSi_DebuggerHandler (.bss) */

#define HW_ITCM_END                  0x02000000
#define OSi_DebuggerHandler          data_020445b4

asm void OSi_ExceptionHandler (void)
{
    ldr r12, = OSi_DebuggerHandler
    ldr r12, [r12]
    cmp r12, #0
    movne lr, pc
    bxne r12
    ldr r12, = HW_ITCM_END
    stmfd r12 !, {r0 - r3, sp, lr}
    and r0, sp, #1
    mov sp, r12
    mrs r1, CPSR
    and r1, r1, #0x1f
    teq r1, #0x17
    bne @10
    bl OSi_GetAndDisplayContext
    b usr_return
@10:
    teq r1, #0x1b
    bne usr_return
    bl OSi_GetAndDisplayContext
usr_return:
    ldr r12, = OSi_DebuggerHandler
    ldr r12, [r12]
    cmp r12, #0
@1:
    beq @1
@2:
    mov r0, r0
    b @2
    ldmfd sp !, {r0 - r3, r12, lr}
    mov sp, r12
    bx lr
}
