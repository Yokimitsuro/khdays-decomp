extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern int func_020018ec(void);
extern void OSi_InsertThreadByPriority(void *thread);
extern void OS_InitContext(void *thread, void *entry, void *stackTop);
extern void OS_SetThreadDestructor(void *thread, void *destructor);
extern void INITi_CpuClear32_0x01ff86fc(int value, void *dst, int size);
extern void func_02001dec(void);

/* Builds a thread control block: links it into the ready queue by priority, paints the stack
 * guard words at both ends and clears the rest of the stack and the TLS slots. */
void OS_CreateThread(char *thread, void (*entry)(void *), void *arg,
                     char *stackTop, unsigned int stackSize, int priority) {
    int enabled = OS_DisableInterrupts();
    char *stackBottom;
    int id;
    id = func_020018ec();
    *(int *)(thread + 0x70) = priority;
    *(int *)(thread + 0x6c) = id;
    *(int *)(thread + 0x64) = 0;
    *(int *)(thread + 0x74) = 0;
    OSi_InsertThreadByPriority(thread);
    *(char **)(thread + 0x94) = stackTop;
    stackBottom = stackTop - stackSize;
    *(char **)(thread + 0x90) = stackBottom;
    *(int *)(thread + 0x98) = 0;
    *(int *)(*(char **)(thread + 0x94) - 4) = 0xfddb597d;
    *(int *)*(char **)(thread + 0x90) = 0x7bf9dd5b;
    *(int *)(thread + 0xa0) = 0;
    *(int *)(thread + 0x9c) = 0;
    OS_InitContext(thread, (void *)entry, stackTop - 4);
    *(void **)(thread + 4) = arg;
    *(void **)(thread + 0x3c) = (void *)&func_02001dec;
    INITi_CpuClear32_0x01ff86fc(0, stackBottom + 4, stackSize - 8);
    *(int *)(thread + 0x84) = 0;
    *(int *)(thread + 0x88) = 0;
    *(int *)(thread + 0x8c) = 0;
    OS_SetThreadDestructor(thread, 0);
    *(int *)(thread + 0x78) = 0;
    *(int *)(thread + 0x80) = 0;
    *(int *)(thread + 0x7c) = 0;
    INITi_CpuClear32_0x01ff86fc(0, thread + 0xa4, 0xc);
    *(int *)(thread + 0xb0) = 0;
    OS_RestoreInterrupts(enabled);
}

/* PARK 2026-07-19: 252/252 bytes, MISMAS instrucciones. Todo casa salvo DONDE materializa mwcc
 * el cero compartido de los campos 0x64 y 0x74:
 *
 *   ROM   bl func_020018ec / ldr r2,[sp,#0x1c] / mov r1,#0 / str r2,[0x70] / str r0,[0x6c]
 *                          / str r1,[0x64] / mov r0,r8 / str r1,[0x74] / bl Insert...
 *   mwcc  ... / str r0,[0x6c] / mov r0,#0 / str r0,[0x64] / str r0,[0x74] / mov r0,r8 / bl
 *
 * El ROM saca el `mov r1,#0` ANTES del store que libera r0, asi que el cero cae en r1; mwcc espera
 * a que r0 quede libre y lo usa. Tabla de los cinco ordenes de fuente probados:
 *
 *   fuente                                   | orden de stores | registro del cero
 *   0x70=prio; 0x6c=call()                   | llamada tarde ✗ | r0 ✗
 *   0x6c=call(); 0x70=prio                   | 0x6c,0x70    ✗  | r0 ✗
 *   id=call(); 0x70; 0x6c; 0x64; 0x74        | correcto     ✓  | r0 ✗   <- ESTA (la mas cercana)
 *   ceros primero, luego llamada             | antes de la llamada ✗ | r1 ✓
 *   id=call(); 0x70; 0x64; 0x6c; 0x74        | 0x70,0x64,0x6c ✗ | r1 ✓
 *
 * O sea: las dos propiedades (orden de stores correcto Y cero en r1) se excluyen con todos los
 * ordenes de sentencia. Probado ademas con una local `int none = 0;` explicita. Clase de
 * planificacion; ver deferred-ties.md. */
