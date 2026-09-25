/* NitroSDK libraries/os/src/os_exception.c: OSi_DisplayExContext (SDK_FINALROM build: the
 * register dump is compiled out; only the user exception handler call remains). C with the
 * SDK's own inline asm block, which switches to system mode, turns the protection unit back on
 * and calls the handler with OSi_ExContext. */
typedef struct OSiExContext OSiExContext;
typedef void (*OSExceptionHandler)(void *context, void *arg);

/* the unit's statics, laid out together in .bss */
typedef struct OSiExceptionStatics {
    void *debuggerHandler;                  /* OSi_DebuggerHandler */
    void *userExceptionHandlerArg;          /* OSi_UserExceptionHandlerArg */
    OSExceptionHandler userExceptionHandler;   /* OSi_UserExceptionHandler */
} OSiExceptionStatics;

extern OSiExceptionStatics data_020445b4;
extern void *data_020445b8;                 /* OSi_UserExceptionHandlerArg */
extern OSExceptionHandler data_020445bc;    /* OSi_UserExceptionHandler */
extern OSiExContext data_020445e0;          /* OSi_ExContext */
extern void OS_EnableProtectionUnit(void);
extern void OS_DisableProtectionUnit(void);

void func_0200302c(void)
{
    if (data_020445b4.userExceptionHandler) {
        asm {
            mrs r2, CPSR
            mov r0, sp
            ldr r1, =0x9f
            msr CPSR_cxsf, r1
            mov r1, sp
            mov sp, r0
            stmfd sp!, {r1, r2}
            bl OS_EnableProtectionUnit
            ldr r0, =data_020445e0
            ldr r1, =data_020445b8
            ldr r1, [r1]
            ldr r12, =data_020445bc
            ldr r12, [r12]
            ldr lr, =@1
            bx r12
        @1:
            bl OS_DisableProtectionUnit
            ldmfd sp!, {r1, r2}
            mov sp, r1
            msr CPSR_cxsf, r2
        }
    }
}
